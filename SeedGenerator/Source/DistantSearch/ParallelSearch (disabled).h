
#include <chrono>
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif
using std::cout;
using std::endl;

#include "OddsCalculator.h"
#include "SearchParameters.h"

#if 0
#elif ENABLE_17_AVX512
#include "TestShiny8_AVX512.h"
#elif ENABLE_13_AVX2
#include "TestShiny4_AVX2.h"
#endif
#include "TestSeed.h"


void search(
    const PokemonSpec& pokemon,
    const SearchFilter& filter,
    const SearchParameters& params
){
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

    uint64_t seed = params.seed();
    uint64_t frames = params.frames();

    params.print();

//    cout << "Starting Seed:    " << std::hex << seed << std::dec << endl;
//    cout << "Frames to Search: " << tostr_commas(frames) << endl;
//    cout << endl;

#ifdef _WIN32
    //  Avoid freezing the system on Windows with 100% CPU usage.
    SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);
#endif

    auto start = std::chrono::system_clock::now();
    PrintReporter reporter(pokemon);

    //  If we're searching only for shinies, we can use the vectorized routines.
#if 0
#elif ENABLE_17_AVX512

    if (filter.shiny & ShinyFilter::NONE){
        cout << "Starting Slow Search..." << endl << endl;
#pragma omp parallel for
        for (int64_t c = 0; c < (int64_t)frames; c++){
            test_seed(reporter, pokemon, filter, seed, c);
        }
    }else{
        cout << "Starting Fast Search (AVX512)..." << endl << endl;
#pragma omp parallel for
        for (int64_t c = 0; c < (int64_t)frames; c += 64){
            test_shiny_AVX512(reporter, pokemon, filter, seed, c, 64);
        }
    }

#elif ENABLE_13_AVX2

    if (filter.shiny & ShinyFilter::NONE){
        cout << "Starting Slow Search..." << endl << endl;
#pragma omp parallel for
        for (int64_t c = 0; c < (int64_t)frames; c++){
            test_seed(reporter, pokemon, filter, seed, c);
        }
    }else{
        cout << "Starting Fast Search (AVX2)..." << endl << endl;
#pragma omp parallel for
        for (int64_t c = 0; c < (int64_t)frames; c += 32){
            test_shiny_AVX2(reporter, pokemon, filter, seed, c, 32);
        }
    }

#else
    cout << "Starting Slow Search..." << endl << endl;

#pragma omp parallel for
    for (int64_t c = 0; c < (int64_t)frames; c++){
        test_seed(reporter, pokemon, filter, seed, c);
    }
#endif

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
//    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//    double secs = millis.count() / 1000.;

    cout << endl;
    cout << "Search Finished: " << diff.count() << " seconds" << endl;
    cout << endl;
}


