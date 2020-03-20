
#pragma once
#ifndef SeedGenerator_SeedPrinter_H
#define SeedGenerator_SeedPrinter_H

#include "PokemonSpec.h"
namespace SeedGenerator{
namespace DistantSearch{

std::string dump_seed(const PokemonSpec& pokemon, uint64_t seed, uint64_t skips);

class SeedReporter{
public:
    virtual void report(uint64_t seed, uint64_t skips) = 0;
};

class PrintReporter : public SeedReporter{
public:
    PrintReporter(const PokemonSpec& pokemon)
        : m_pokemon(pokemon)
    {}

    virtual void report(uint64_t seed, uint64_t skips) override;

private:
    const PokemonSpec& m_pokemon;
};

}
}
#endif
