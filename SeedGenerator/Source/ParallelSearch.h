
#include <chrono>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "OddsCalculator.h"

#if 0
#elif ENABLE_AVX512
#include "TestSeed8_AVX512.h"
#elif ENABLE_AVX2
#include "TestSeed4_AVX2.h"
#else
#include "TestSeed1.h"
#endif


void search(const Pokemon& pokemon, const Filter& filter, uint64_t seed, uint64_t frames){
    pokemon.print();
    filter.print();
    try{
        print_odds(pokemon, filter);
    }catch (const char* str){
        cout << endl;
        cout << str << endl;
        cout << "Canceling Search..." << endl;
        cout << endl;
        return;
    }
    cout << endl;

    cout << "Starting Seed:    " << std::hex << seed << std::dec << endl;
    cout << "Frames to Search: " << tostr_commas(frames) << endl;
    cout << endl;

#ifdef _WIN32
    //  Avoid freezing the system on Windows with 100% CPU usage.
    SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);
#endif

    auto start = std::chrono::system_clock::now();

    //  If we're searching only for shinies, we can use the vectorized routines.
#if 0
#elif ENABLE_AVX512

    if (filter.shiny & ShinyFilter::NONE){
        cout << "Starting Slow Search..." << endl << endl;
#pragma omp parallel for
        for (int64_t c = 0; c < (int64_t)frames; c++){
            test_seed(pokemon, filter, seed, c);
        }
    }else{
        cout << "Starting Fast Search (AVX512)..." << endl << endl;
#pragma omp parallel for
        for (int64_t c = 0; c < (int64_t)frames; c += 8){
            test_seed8(pokemon, filter, seed, c);
        }
    }

#elif ENABLE_AVX2

    if (filter.shiny & ShinyFilter::NONE){
        cout << "Starting Slow Search..." << endl << endl;
#pragma omp parallel for
        for (int64_t c = 0; c < (int64_t)frames; c++){
            test_seed(pokemon, filter, seed, c);
        }
    }else{
        cout << "Starting Fast Search (AVX2)..." << endl << endl;
#pragma omp parallel for
        for (int64_t c = 0; c < (int64_t)frames; c += 4){
            test_seed4(pokemon, filter, seed, c);
        }
    }

#else
    cout << "Starting Slow Search..." << endl << endl;

#pragma omp parallel for
    for (int64_t c = 0; c < (int64_t)frames; c++){
        test_seed(pokemon, filter, seed, c);
    }
#endif

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;

    cout << endl;
    cout << "Search Finished: " << diff.count() << " seconds" << endl;
    cout << endl;
}


