
#include "Tools.h"


int main(){

    //  Parameter 1: Abilities
    //      HIDDEN      hidden ability possible
    //      NO_HIDDEN   hidden ability not possible
    //      LOCKED      ability locked (not tested)
    //
    //  Parameter 2: # of max IVs
    //
    //  Parameter 3: Gender
    //      true        multiple genders are possible
    //      false       mono-gender pokemon or gender-locked raid
    Pokemon pokemon{Ability::HIDDEN, 4, false};

    //  Parameter 1: Shininess
    //      NONE, STAR, SQUARE, or UNSPECIFIED
    //      UNSPECIFIED disables the filter
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
    Filter filter{Shiny::SQUARE, {31, 0, 31, 31, 31, 0}, 2, Nature::Quiet};

    //  Starting seed.
    u64 seed = 0x62533d674d4772d2;


#pragma omp parallel for
    for (int64_t c = 0; c < 1'000'000'000'000; c++){
        test_seed(pokemon, filter, seed, c);
    }


    system("pause");
}


