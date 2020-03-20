
#pragma once
#ifndef SeedGenerator_PokemonSpec_H
#define SeedGenerator_PokemonSpec_H

#include <fstream>
#include "Fields/Types.h"
#include "Fields/Gender.h"
namespace SeedGenerator{


class PokemonSpec{
public:
    PokemonSpec() = default;
    PokemonSpec(
        int max_ivs,
        Ability ability,
        GenderRatio gender
    );

    PokemonSpec(std::istream& stream);

    void print() const;

    int         max_ivs () const{ return m_max_ivs; }
    Ability     ability () const{ return m_ability; }
    GenderRatio gender  () const{ return m_gender; }

public:
    static void parse_max_ivs(const char*& stream, PokemonSpec& self);
    static void parse_ability(const char*& stream, PokemonSpec& self);
    static void parse_gender(const char*& stream, PokemonSpec& self);

private:
    int         m_max_ivs = 1;
    Ability     m_ability = Ability::NO_HIDDEN;
    GenderRatio m_gender  = GenderRatio::FEMALE;
};


}
#endif
