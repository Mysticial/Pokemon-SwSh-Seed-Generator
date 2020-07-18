
#include <algorithm>
#include <vector>
#include <atomic>
#include <thread>
#include <iostream>

#if 0
#elif ENABLE_17_AVX512
#include "ScanSeed8_AVX512.h"
#elif ENABLE_13_AVX2
#include "ScanSeed4_AVX2.h"
#elif ENABLE_07_SSE41
#include "ScanSeed2_SSE41.h"
#else
#include "ScanSeed_Default.h"
#endif

#include "CalculateSeed.h"
using std::cout;
using std::endl;

namespace SeedGenerator{
namespace SeedCalculator{


uint64_t test_seed(const CalculateSeedParameters& params, uint64_t seed, uint64_t iterations){
    if (iterations == 0){
        return 0;
    }

#if 0
#elif ENABLE_17_AVX512
    return test_seed_AVX512(params, seed, iterations);
#elif ENABLE_13_AVX2
    return test_seed_AVX2(params, seed, iterations);
#elif ENABLE_07_SSE41
    return test_seed_SSE41(params, seed, iterations);
#else
    return test_seed_Default(params, seed, iterations);
#endif
}

void calculate_shiny(const CalculateSeedParameters& params){
//    bool squares = params.shiny() == ShinyType::SQUARE;
    uint32_t ec = params.ec();
    uint32_t pid = params.pid();

//    cout << "Finding Seed for Shiny:" << endl;
//    cout << "    Shiny = " << (squares ? "Square" : "Star") << endl;
//    cout << "    EC    = " << std::hex << ec << endl;
//    cout << "    PID   = " << std::hex << pid << endl;
//    cout << endl;

    uint16_t pid16 = (uint16_t)pid;
    uint32_t seed32 = (uint32_t)(ec - 0x82A2B175229D6A5B);

    cout << "Searching..." << endl;
    cout << endl;

    auto start = std::chrono::system_clock::now();
    uint64_t iterations = 0x100000000;

    std::vector<std::thread> threads(std::thread::hardware_concurrency());
    uint64_t block = (iterations - 1) / threads.size() + 1;

    std::atomic<uint64_t> found(0);
    for (size_t c = 0; c < threads.size(); c++){
        threads[c] = std::thread([=, &found, &params]{
            uint64_t s = c * block;
            uint64_t e = s + block;
            e = std::min(e, iterations);
            if (s >= e){
                return;
            }
            found += test_seed(params, seed32 | (s << 32), e - s);
        });
    }

    for (std::thread& thread : threads){
        thread.join();
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;

    cout << endl;
    cout << "Search Finished: " << diff.count() << " seconds" << endl;
    cout << endl;

    if (found == 0){
        cout << "No seeds found. Input is either incorrect or the pokemon is hacked/illegal." << endl;
    }else if (found > 10){
        cout << "Many seeds found. Try making the filters more specific." << endl;
        cout << "Note that if this is a forced shiny, there may legit be many possible seeds." << endl;
    }else{
        cout << "Seed(s) found. For legality checking, please verify remaining stats with RaidFinder." << endl;
    }
    cout << endl;
}

void calculate_seed(std::istream& stream){
    CalculateSeedParameters params;

    std::string line;
    while (std::getline(stream, line)){
        if (line.empty()){
            continue;
        }
        if (line == "CalculateSeed:"){
            params = CalculateSeedParameters(stream);
            continue;
        }
    }

    params.print();
    calculate_shiny(params);
}




}
}
