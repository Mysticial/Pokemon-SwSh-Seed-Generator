
#pragma once
#ifndef SeedGenerator_TestShiny8_H
#define SeedGenerator_TestShiny8_H

#include "PokemonSpec.h"
#include "SearchFilter.h"
#include "TestSeed.h"
namespace SeedGenerator{
namespace DistantSearch{


void test_shiny_AVX512(
    SeedReporter& reporter,
    const PokemonSpec& pokemon,
    const SearchFilter& filter,
    uint64_t seed, uint64_t skips,
    uint64_t iterations
);

inline void test_seed_AVX512(
    SeedReporter& reporter,
    const PokemonSpec& pokemon,
    const SearchFilter& filter,
    uint64_t seed, uint64_t skips,
    uint64_t iterations
){
    if (filter.shiny & ShinySearchFilter::NONE){
        test_seed_Default(reporter, pokemon, filter, seed, skips, iterations);
    }
    test_shiny_AVX512(reporter, pokemon, filter, seed, skips, iterations);
}



}
}
#endif
