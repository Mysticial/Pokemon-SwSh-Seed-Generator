
#include <array>
#include <vector>
#include <iostream>
#include "Tools/Tools.h"

#include "OddsCalculator.h"
using std::cout;
using std::endl;

namespace SeedGenerator{
namespace DistantSearch{

double odds_shiny(ShinySearchFilter shiny){
    double odds = 0;
    if (shiny & ShinySearchFilter::NONE){
        odds += 4095/4096.;
    }
    if (shiny & ShinySearchFilter::STAR){
        odds += 15/65536.;
    }
    if (shiny & ShinySearchFilter::SQUARE){
        odds += 1/65536.;
    }
    if (odds == 0){
        throw "No shiny status is selected.";
    }

    odds = 1 / odds;

    cout << "    Shininess:     1 in " << tostr_commas((uint64_t)odds) << endl;
    return odds;
}

double odds_gender(GenderRatio ratio, GenderFilter filter){
    if (ratio == GenderRatio::GENDERLESS && filter != GenderFilter::UNSPECIFIED){
        throw "No hits possible. Pokemon is genderless. Please remove gender filter.";
    }
    if (ratio == GenderRatio::MALE && filter == GenderFilter::FEMALE){
        throw "No hits possible. Pokemon is 100% male. Please remove gender filter.";
    }
    if (ratio == GenderRatio::FEMALE && filter == GenderFilter::MALE){
        throw "No hits possible. Pokemon is 100% female. Please remove gender filter.";
    }
    if (filter == GenderFilter::UNSPECIFIED){
        return 1;
    }

    double odds = 1;
    switch (ratio){
    case GenderRatio::MALE_88:
        odds = filter == GenderFilter::FEMALE ? 8. : 8/7.;
        break;
    case GenderRatio::MALE_75:
        odds = filter == GenderFilter::FEMALE ? 4. : 4/3.;
        break;
    case GenderRatio::EVEN:
        odds = 2;
        break;
    case GenderRatio::FEMALE_75:
        odds = filter == GenderFilter::FEMALE ? 4/3. : 4.;
        break;
    case GenderRatio::FEMALE_88:
        odds = filter == GenderFilter::FEMALE ? 8/7. : 8.;
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

double binomial_probability(size_t n, size_t k, double p){
    double num = 1;
    double den = 1;
    for (size_t c = 0; c < k; c++){
        num *= n - c;
        den *= c + 1;
    }
    num *= std::pow(p, k);
    num *= std::pow(1 - p, n - k);
    return num / den;
}
double odds_mask(const std::array<char, 6>& mask, const IvFilter& ivs){
    //  Return the probability of the mask satisfying the desired IV spread.
    int max_IVs = 0;
    int flex_IVs = 0;

    double odds_IVs = 1;
    for (int c = 0; c < 6; c++){
        char desired = ivs[c];
        if (c == ivs.characteristic()){
            if (0 <= desired && desired < 31){
                return 0;
            }
            desired = 31;
        }
        if (mask[c]){
            //  Forced to 31
            if (0 <= desired && desired < 31){
                return 0;
            }
            max_IVs++;
        }else{
            //  Randomized
            if (desired == 31){
                odds_IVs *= 1 / 32.;
                max_IVs++;
            }else if (0 <= desired){
                odds_IVs *= 1 / 32.;
            }else{
                flex_IVs++;
            }
        }
    }

    if (ivs.characteristic() < 0){
        return odds_IVs;
    }

    double odds_characteristic = 0;
    for (int c = 0; c <= flex_IVs; c++){
        odds_characteristic += binomial_probability(flex_IVs, c, 1/32.) / (max_IVs + c);
    }

    return odds_IVs * odds_characteristic;
}
double odds_set(const std::vector<std::array<char, 6>>& masks, const IvFilter& ivs){
    //  Return the probability of the max IV set satisfying the desired IV spread.
    double odds = 0;
    for (const std::array<char, 6>& mask : masks){
        //cout << (int)mask[0] << " "
        //     << (int)mask[1] << " "
        //     << (int)mask[2] << " "
        //     << (int)mask[3] << " "
        //     << (int)mask[4] << " "
        //     << (int)mask[5] << " - " << 1 / odds_mask(mask, ivs) << endl;
        odds += odds_mask(mask, ivs);
    }
    return odds / masks.size();
}
double odds_ivs(int max_ivs, const IvFilter& ivs){
    //  This one is ugly to calculate.

    //  For a given # of max IVs, brute force all the different
    //  "masks" (permutations of max IVs) and calculate the probability that
    //  each mask is satisfied. Add it all up and divide by the total # of masks.

    if (max_ivs < 0 || max_ivs > 6){
        throw "Max IVs must be 0 - 6.";
    }

    double odds = odds_set(MASKS[max_ivs], ivs);
    if (odds == 0){
        throw "Impossible to satisfy the desired IV spread and/or characteristic.";
    }

    odds = 1 / odds;
    if (ivs.characteristic() < 0){
        cout << "    IV Spread:     1 in " << tostr_commas((uint64_t)odds) << endl;
    }else{
        cout << "    IV Spread:     1 in " << tostr_commas((uint64_t)odds) << "  (including characteristic)" << endl;
    }

    return odds;
}

uint64_t print_odds(const PokemonSpec& pokemon, const SearchFilter& filter){
    cout << "Odds:" << endl;

    double odds = 1;

    //  Shiny
    odds *= odds_shiny(filter.shiny);

    //  IVs
    odds *= odds_ivs(pokemon.max_ivs(), filter.IVs);

    //  Nature
    if (filter.nature != Nature::UNSPECIFIED){
        odds *= 25;
        cout << "    Nature:        1 in 25" << endl;
    }

    //  Gender
    odds *= odds_gender(pokemon.gender(), filter.gender);

    if (odds == 0){
        cout << "Unable to calculate odds." << endl;
        return 0;
    }

    //  Ability
    if (filter.ability == -1){
        cout << "    Total:         1 in " << tostr_commas((uint64_t)odds) << endl;
        return (uint64_t)odds;
    }

    switch (pokemon.ability()){
    case Ability::HIDDEN:
        odds *= 3;
        cout << "    Ability:       1 in 3" << endl;
        break;
    case Ability::NO_HIDDEN:
        if (filter.ability == 2){
            throw "No hits possible. This pokemon does not have hidden ability.";
        }
        odds *= 2;
        cout << "    Ability:       1 in 2" << endl;
        break;
    case Ability::LOCKED:
        cout << "    Ability:       ignored" << endl;
        break;
    }
    cout << "    Total Odds:    1 in " << tostr_commas((uint64_t)odds) << endl;

    return (uint64_t)odds;
}



}
}

