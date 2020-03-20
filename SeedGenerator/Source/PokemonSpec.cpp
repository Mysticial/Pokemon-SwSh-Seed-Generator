
#include <map>
#include <iostream>
#include "Tools/Tools.h"
#include "PokemonSpec.h"
using std::cout;
using std::endl;

namespace SeedGenerator{


const std::map<std::string, void(*)(const char*&, PokemonSpec&)> POKEMON_SPEC_KEYS{
    {"GuaranteedMaxIVs:",       PokemonSpec::parse_max_ivs},
    {"HiddenAbilityPossible:",  PokemonSpec::parse_ability},
    {"GenderRatio:",            PokemonSpec::parse_gender},
};

void PokemonSpec::parse_max_ivs(const char*& stream, PokemonSpec& self){
    skip_whitespace(stream);
    uint64_t x = parse_dec(stream);
    if (x < 1 || x > 6){
        throw "# of Max IVs must be between 1 and 6 inclusive.";
    }
    self.m_max_ivs = (int)x;
}
void PokemonSpec::parse_ability(const char*& stream, PokemonSpec& self){
    skip_whitespace(stream);
    std::string token = parse_token(stream);
    if (token == "yes"){
        self.m_ability = Ability::HIDDEN;
        return;
    }
    if (token == "no"){
        self.m_ability = Ability::NO_HIDDEN;
        return;
    }
    throw "Invalid hidden ability specifier: " + token;
}
void PokemonSpec::parse_gender(const char*& stream, PokemonSpec& self){
    skip_whitespace(stream);
    std::string token = parse_token(stream);
    self.m_gender = read_genderratio(token);
}


PokemonSpec::PokemonSpec(
    int max_ivs,
    Ability ability,
    GenderRatio gender
)
    : m_max_ivs(max_ivs)
    , m_ability(ability)
    , m_gender(gender)
{}
PokemonSpec::PokemonSpec(std::istream& stream){
    std::string line;
    while (std::getline(stream, line)){
        if (line.empty()){
            return;
        }
        const char* str = line.c_str();
        skip_whitespace(str);
        std::string token = parse_token(str);
        if (token.empty()){
            continue;
        }

        auto iter = POKEMON_SPEC_KEYS.find(token);
        if (iter == POKEMON_SPEC_KEYS.end()){
            throw "Unrecognized Token: " + token;
        }

        if (iter->second == nullptr){
            continue;
        }
        iter->second(str, *this);
    }
}

void PokemonSpec::print() const{
    cout << "Pokemon Spec:" << endl;

    cout << "    Max IVs:    " << m_max_ivs << endl;

    switch (m_ability){
    case Ability::HIDDEN: cout << "    Ability:    hidden possible" << endl;
        break;
    case Ability::NO_HIDDEN:
        cout << "    Ability:    hidden not possible" << endl;
        break;
    case Ability::LOCKED:
        cout << "    Ability:    locked" << endl;
        break;
    }

    cout << "    Gender:     " << to_string(m_gender) << endl;
    cout << endl;
}

}
