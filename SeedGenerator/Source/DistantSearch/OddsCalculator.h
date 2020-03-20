
#pragma once
#ifndef SeedGenerator_OddsCalculator_H
#define SeedGenerator_OddsCalculator_H

#include "PokemonSpec.h"
#include "SearchFilter.h"
namespace SeedGenerator{
namespace DistantSearch{


double odds_shiny(ShinyFilter shiny);
double odds_gender(GenderRatio ratio, GenderFilter filter);
double odds_ivs(int max_ivs, const IvFilter& ivs);

uint64_t print_odds(const PokemonSpec& pokemon, const SearchFilter& filter);


}
}
#endif
