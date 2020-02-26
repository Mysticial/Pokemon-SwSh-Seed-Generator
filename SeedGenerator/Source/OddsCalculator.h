
#pragma once
#ifndef SeedGenerator_OddsCalculator_H
#define SeedGenerator_OddsCalculator_H

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
    return 1 / odds;
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
    switch (ratio){
        case GenderRatio::MALE_88:
            return filter == Gender::FEMALE ? 8 : 7/8.;
            break;
        case GenderRatio::MALE_75:
            return filter == Gender::FEMALE ? 4 : 3/4.;
            break;
        case GenderRatio::EVEN:
            return 2;
            break;
        case GenderRatio::FEMALE_75:
            return filter == Gender::FEMALE ? 3/4. : 4;
            break;
        case GenderRatio::FEMALE_88:
            return filter == Gender::FEMALE ? 7/8. : 8;
            break;
    }
}

double odds_ivs(int max_ivs, const int filter_ivs[6]){
    int dont_care_ivs = 0;
    int required_max_ivs = 0;
    int required_non_max_ivs = 0;
    for (size_t c = 0; c < 6; c++){
        int iv = filter_ivs[c];
        if (iv == -1){
            dont_care_ivs++;
            continue;
        }
        if (iv == 31){
            required_max_ivs++;
        }else{
            required_non_max_ivs++;
        }
    }
    if (required_non_max_ivs + max_ivs > 6){
        throw "No hits possible. Too many non-max IVs. Please adjust IV filter.";
    }

    switch (max_ivs){
    case 1:
    case 2:
    case 3:
        return 0;
    case 4:{
        const double TABLE[][7] = {
            {1, 96/65., 15360/6401., 512/109., 7680/643., 1536/17., 1024},  //  0 required non-max IVs
            {96, 5120/43., 7680/49., 15360/67., 1280/3., 3072, 0},          //  1 required non-max IVs
            {15360, 15360, 15360, 15360, 15360, 0, 0},                      //  2 required non-max IVs
        };
        return TABLE[required_non_max_ivs][required_max_ivs];
    }case 5:
        if (required_max_ivs == 6){
            return 32;
        }
        if (required_non_max_ivs == 1){
            return 196;
        }else{
            return 6;
        }
    default:
        throw "Max IVs must be 1 - 5.";
    }
}


void print_odds(const Pokemon& pokemon, const Filter& filter){
    double odds = 1;

    //  Shiny
    odds *= odds_shiny(filter.shiny);

    //  Nature
    if (filter.nature != Nature::UNSPECIFIED){
        odds *= 25;
    }

    //  Gender
    odds *= odds_gender(pokemon.gender, filter.gender);

    //  IVs
    odds *= odds_ivs(pokemon.max_ivs, filter.IVs);


    //  Ability
    if (pokemon.ability == Ability::NO_HIDDEN && filter.ability == 2){
        throw "No hits possible. Hidden ability selected when not possible.";
    }
    if (pokemon.ability == Ability::LOCKED && filter.ability != -1){
        cout << "Ability is locked. Ignoring ability filter." << endl;
    }

    if (odds == 0){
        cout << "Unable to calculate odds." << endl;
        return;
    }

    switch (filter.ability){
    case -1:
        cout << "Odds: 1 in " << (odds == 0 ? "Unable to compute." : tostr_commas((uint64_t)odds)) << endl;
        break;
    case 2:
        odds *= 3;
        cout << "Odds: 1 in " << (odds == 0 ? "Unable to compute." : tostr_commas((uint64_t)odds)) << endl;
        break;
    case 0:
        double odds2 = odds;
        if (pokemon.ability == Ability::HIDDEN){
            odds2 *= 2;
        }
        cout << "Odds (1 non-HA ability):   1 in " << (odds == 0 ? "Unable to compute." : tostr_commas((uint64_t)odds)) << endl;
        cout << "Odds (2 non-HA abilities): 1 in " << (odds == 0 ? "Unable to compute." : tostr_commas((uint64_t)odds2)) << endl;
        break;
    }
}

#endif
