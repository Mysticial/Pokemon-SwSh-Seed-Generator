
#pragma once
#ifndef SeedGenerator_TestSeed_H
#define SeedGenerator_TestSeed_H

#include "SeedPrinter.h"
#include "PokemonSpec.h"
#include "SearchFilter.h"
namespace SeedGenerator{
namespace DistantSearch{


void test_seed(
    SeedReporter& reporter,
    const PokemonSpec& pokemon,
    const SearchFilter& filter,
    uint64_t seed, uint64_t skips
);

void test_seed_Default(
    SeedReporter& reporter,
    const PokemonSpec& pokemon,
    const SearchFilter& filter,
    uint64_t seed, uint64_t skips,
    uint64_t iterations
);



}
}
#endif
