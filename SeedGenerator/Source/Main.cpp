
#include "ParallelSearch.h"



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
    //  Parameter 3: Characteristic
    //      -1      Don't filter.
    //      0       Takes plenty of siestas
    //      1       Likes to thrash about
    //      2       Capable of taking hits
    //      3       Mischievous
    //      4       Somewhat vain
    //      5       Alert to sounds
    //
    //  Parameter 4: Ability
    //      -1      Don't filter
    //      0       Ability 1
    //      1       Ability 2
    //      2       Hidden Ability
    //
    //  Parameter 5: Nature
    //      UNSPECIFIED means don't filter.
    //
    //  Parameter 6: Gender
    //      MALE
    //      FEMALE
    //      UNSPECIFIED means don't filter.

    Filter filter{
        ShinyFilter::SQUARE,
        {31, 0, 31, 31, 31, 0},
        3,
        2,
        Nature::Quiet,
        Gender::FEMALE,
    };

    //  Starting seed.
    u64 seed = 0x4399E7E35F921E09;

    //  Frames to search.
    u64 frames = 1'000'000'000'000;


    //  Perform search.
    search(pokemon, filter, seed, frames);

#ifdef _WIN32
    system("pause");
#endif
}


