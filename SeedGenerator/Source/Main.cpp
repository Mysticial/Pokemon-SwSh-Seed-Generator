
#include <chrono>
#include <Windows.h>
#include "OddsCalculator.h"

#if 0
#elif ENABLE_AVX512
#include "TestSeed8_AVX512.h"
#elif ENABLE_AVX2
#include "TestSeed4_AVX2.h"
#else
#include "TestSeed1.h"
#endif



int main(){

    //  Parameter 1: Abilities
    //      HIDDEN      hidden ability possible
    //      NO_HIDDEN   hidden ability not possible
    //      LOCKED      ability locked (not tested)
    //
    //  Parameter 2: # of max IVs
    //
    //  Parameter 3: Gender
    //      MALE        100% male
    //      MALE_88     88% male
    //      MALE_75     75% male
    //      EVEN        50%
    //      FEMALE_75   75% female
    //      FEMALE_88   88% female
    //      FEMALE     100% female
    //      GENDERLESS
    Pokemon pokemon{
        Ability::HIDDEN,
        4,
        GenderRatio::FEMALE,
    };

    //  Parameter 1: Shininess
    //      NONE        not shiny
    //      STAR        star shinies
    //      SQUARE      square shinies
    //      SHINY       star or square shinies
    //      ALL         include everything
    //  You can combine multiple flags to include in the filter.
    //
    //  Parameter 2: IVs
    //      -1      Don't filter.
    //      x       Show only this specific value.
    //
    //  Parameter 3: Ability
    //      -1      Don't filter
    //      0       Ability 1
    //      1       Ability 2
    //      2       Hidden Ability
    //
    //  Parameter 4: Nature
    //      UNSPECIFIED means don't filter.
    //
    //  Parameter 5: Gender
    //      MALE
    //      FEMALE
    //      UNSPECIFIED means don't filter.

    Filter filter{
        ShinyFilter::SQUARE,
        {31, 0, 31, 31, 31, 0},
        2,
        Nature::Quiet,
        Gender::FEMALE,
    };

    //  Starting seed.
    u64 seed = 0x62533d674d4772d2;

    //  Frames to search.
    u64 frames = 1'000'000'000'000;






    pokemon.print();
    filter.print();
    try{
        print_odds(pokemon, filter);
    }catch (const char* str){
        cout << str << endl;
        cout << "Canceling Search..." << endl;
        cout << endl;
        system("pause");
        return 1;
    }
    cout << endl;

    cout << "Starting Seed: " << std::hex << seed << std::dec << endl;
    cout << endl;

    //  Avoid freezing the system on Windows with 100% CPU usage.
    SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);

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
    system("pause");
}


