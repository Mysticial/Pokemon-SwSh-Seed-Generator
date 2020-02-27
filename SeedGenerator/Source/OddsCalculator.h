
#pragma once
#ifndef SeedGenerator_OddsCalculator_H
#define SeedGenerator_OddsCalculator_H

#include <array>
#include <iostream>
#include "Types.h"
using std::cout;
using std::endl;


double odds_shiny(ShinyFilter shiny){
    double odds = 0;
    if (shiny & ShinyFilter::NONE){
        odds += 4095/4096.;
    }
    if (shiny & ShinyFilter::STAR){
        odds += 15/65536.;
    }
    if (shiny & ShinyFilter::SQUARE){
        odds += 1/65536.;
    }
    if (odds == 0){
        throw "No shiny status is selected.";
    }

    odds = 1 / odds;

    cout << "    Shininess:     1 in " << tostr_commas((uint64_t)odds) << endl;
    return odds;
}

double odds_gender(GenderRatio ratio, Gender filter){
    if (ratio == GenderRatio::GENDERLESS && filter != Gender::UNSPECIFIED){
        throw "No hits possible. Pokemon is genderless. Please remove gender filter.";
    }
    if (ratio == GenderRatio::MALE && filter == Gender::FEMALE){
        throw "No hits possible. Pokemon is 100% male. Please remove gender filter.";
    }
    if (ratio == GenderRatio::FEMALE && filter == Gender::MALE){
        throw "No hits possible. Pokemon is 100% female. Please remove gender filter.";
    }
    if (filter == Gender::UNSPECIFIED){
        return 1;
    }

    double odds = 1;
    switch (ratio){
    case GenderRatio::MALE_88:
        odds = filter == Gender::FEMALE ? 8. : 8/7.;
        break;
    case GenderRatio::MALE_75:
        odds = filter == Gender::FEMALE ? 4. : 4/3.;
        break;
    case GenderRatio::EVEN:
        odds = 2;
        break;
    case GenderRatio::FEMALE_75:
        odds = filter == Gender::FEMALE ? 4/3. : 4.;
        break;
    case GenderRatio::FEMALE_88:
        odds = filter == Gender::FEMALE ? 8/7. : 8.;
        break;
    default:
        odds = 1;
    }

    cout << "    Gender:        1 in " << odds << endl;
    return odds;
}

const std::vector<std::array<char, 6>> MASKS[7] = {
    {
        {0, 0, 0, 0, 0, 0},
    },
    {
        {1, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 1},
    },
    {
        {1, 1, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0},
        {1, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 1},
        {0, 1, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 1},
        {0, 0, 1, 1, 0, 0},
        {0, 0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0, 1},
        {0, 0, 0, 1, 1, 0},
        {0, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 1, 1},
    },
    {
        {1, 1, 1, 0, 0, 0},
        {1, 1, 0, 1, 0, 0},
        {1, 1, 0, 0, 1, 0},
        {1, 1, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0},
        {1, 0, 1, 0, 1, 0},
        {1, 0, 1, 0, 0, 1},
        {1, 0, 0, 1, 1, 0},
        {1, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 1},
        {0, 1, 1, 1, 0, 0},
        {0, 1, 1, 0, 1, 0},
        {0, 1, 1, 0, 0, 1},
        {0, 1, 0, 1, 1, 0},
        {0, 1, 0, 1, 0, 1},
        {0, 1, 0, 0, 1, 1},
        {0, 0, 1, 1, 1, 0},
        {0, 0, 1, 1, 0, 1},
        {0, 0, 1, 0, 1, 1},
        {0, 0, 0, 1, 1, 1},
    },
    {
        {1, 1, 1, 1, 0, 0},
        {1, 1, 1, 0, 1, 0},
        {1, 1, 1, 0, 0, 1},
        {1, 1, 0, 1, 1, 0},
        {1, 1, 0, 1, 0, 1},
        {1, 1, 0, 0, 1, 1},
        {1, 0, 1, 1, 1, 0},
        {1, 0, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 1},
        {1, 0, 0, 1, 1, 1},
        {0, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 0, 1},
        {0, 1, 1, 0, 1, 1},
        {0, 1, 0, 1, 1, 1},
        {0, 0, 1, 1, 1, 1},
    },
    {
        {1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 1},
        {1, 1, 0, 1, 1, 1},
        {1, 0, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1},
    },
    {
        {1, 1, 1, 1, 1, 1},
    },
};

double odds_mask(const std::array<char, 6>& mask, const int ivs[6]){
    //  Return the probability of the mask satisfying the desired IV spread.
    double odds = 1;
    for (size_t c = 0; c < 6; c++){
        int desired = ivs[c];
        if (mask[c]){
            //  Forced to 31
            if (0 <= desired && desired < 31){
                return 0;
            }
        }else{
            //  Randomized
            if (0 <= desired){
                odds *= 1 / 32.;
            }
        }
    }
    return odds;
}
double odds_set(const std::vector<std::array<char, 6>>& masks, const int ivs[6]){
    //  Return the probability of the max IV set satisfying the desired IV spread.
    double odds = 0;
    for (const std::array<char, 6>& mask : masks){
        odds += odds_mask(mask, ivs);
    }
    return odds / masks.size();
}
double odds_ivs(int max_ivs, const int filter_ivs[6]){
    //  This one is ugly to calculate.

    //  For a given # of max IVs, brute force all the different
    //  "masks" (permutations of max IVs) and calculate the probability that
    //  each mask is satisfied. Add it all up and divide by the total # of masks.

    if (max_ivs < 0 || max_ivs > 6){
        throw "Max IVs must be 0 - 6.";
    }

    double odds = odds_set(MASKS[max_ivs], filter_ivs);
    if (odds == 0){
        throw "Impossible to satisfy the desired IV spread.";
    }

    odds = 1 / odds;
    cout << "    IV Spread:     1 in " << tostr_commas((uint64_t)odds) << endl;

    return odds;
}


void print_odds(const Pokemon& pokemon, const Filter& filter){
    cout << "Odds:" << endl;

    double odds = 1;

    //  Shiny
    odds *= odds_shiny(filter.shiny);

    //  IVs
    odds *= odds_ivs(pokemon.max_ivs, filter.IVs);

    //  Nature
    if (filter.nature != Nature::UNSPECIFIED){
        odds *= 25;
        cout << "    Nature:        1 in 25" << endl;
    }

    //  Gender
    odds *= odds_gender(pokemon.gender, filter.gender);

    if (odds == 0){
        cout << "Unable to calculate odds." << endl;
        return;
    }

    //  Ability
    if (filter.ability == -1){
        cout << "  Total:         1 in " << tostr_commas((uint64_t)odds) << endl;
        return;
    }

    switch (pokemon.ability){
    case Ability::HIDDEN:
        odds *= 3;
        cout << "    Ability:       1 in 3" << endl;
        //if (filter.ability == 2){
        //    cout << "    Ability:       1 in 3" << endl;
        //    cout << "    Total Odds:    1 in " << tostr_commas((uint64_t)odds) << endl;
        //}else{
        //    cout << "    Ability:       (1 in 3) or (2 in 3)" << endl;
        //    cout << "    Total (1 non-HA ability):   1 in " << tostr_commas((uint64_t)(odds * 0.5)) << endl;
        //    cout << "    Total (2 non-HA abilities): 1 in " << tostr_commas((uint64_t)odds) << endl;
        //}
        break;
    case Ability::NO_HIDDEN:
        odds *= 2;
        cout << "    Ability:       1 in 2" << endl;
        //if (filter.ability == 2){
        //    cout << "    Ability:       1 in 3" << endl;
        //    cout << "    Total:         1 in " << tostr_commas((uint64_t)odds) << endl;
        //    return;
        //}else{
        //    cout << "    Ability:       (1 in 3) or (2 in 3)" << endl;
        //    cout << "    Total (1 non-HA ability):   1 in " << tostr_commas((uint64_t)(odds * 0.5)) << endl;
        //    cout << "    Total (2 non-HA abilities): 1 in " << tostr_commas((uint64_t)odds) << endl;
        //    return;
        //}
        break;
    case Ability::LOCKED:
        cout << "    Ability:       ignored" << endl;
        break;
    }
    cout << "    Total Odds:    1 in " << tostr_commas((uint64_t)odds) << endl;
}

#endif
