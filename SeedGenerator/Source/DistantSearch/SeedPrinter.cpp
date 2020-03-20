
#include <sstream>
#include <iostream>
#include "Tools/Tools.h"
#include "Tools/XoroShiro.h"
#include "Fields/Nature.h"
#include "SeedPrinter.h"
namespace SeedGenerator{
namespace DistantSearch{


std::string dump_seed(const PokemonSpec& pokemon, uint64_t seed, uint64_t skips){
    XoroShiro rng(seed);

    u32 ec = rng.nextInt(0xffffffff);

    u32 sidtid = rng.nextInt(0xffffffff);
    u32 pid = rng.nextInt(0xffffffff);

    u16 ftsv = getSv(sidtid);
    u16 psv = getSv(pid);

    int shiny = 0;
    if (ftsv == psv){
        shiny = getShinyType(sidtid, pid);
//        cout << "Shiny = " << shiny << endl;
    }

    char IVs[6] = {-1, -1, -1, -1, -1, -1};
    char characteristic = -1;
    int ability = -1;
    int gender_id = -1;
    int nature;

    //  Forced max IVs.
    for (u8 i = 0; i < pokemon.max_ivs();){
        u8 index = static_cast<u8>(rng.nextInt(6, 7));
        if (IVs[index] == -1)
        {
            IVs[index] = 31;
            i++;
        }
    }

    // Fill rest of IVs with rand calls
    for (u8 i = 0; i < 6; i++){
        if (IVs[i] == -1){
            IVs[i] = static_cast<u8>(rng.nextInt(31));
        }
//        cout << "IV = " << IVs[i] << endl;
    }

    //  Characteristic
    characteristic = getCharacteristic(ec, IVs);

    //  Ability
    switch (pokemon.ability()){
    case Ability::HIDDEN:
        ability = static_cast<u8>(rng.nextInt(3, 3));
        break;
    case Ability::NO_HIDDEN:
        ability = static_cast<u8>(rng.nextInt(1));
        break;
    case Ability::LOCKED:
        ability = -1;
        break;
    }

    //  Gender
    GenderFilter gender;
    switch (pokemon.gender()){
    case GenderRatio::GENDERLESS:
        gender = GenderFilter::UNSPECIFIED;
        break;
    case GenderRatio::FEMALE:
        gender = GenderFilter::FEMALE;
        break;
    case GenderRatio::MALE:
        gender = GenderFilter::MALE;
        break;
    default:
        gender_id = static_cast<u8>(rng.nextInt(253, 255) + 1);
        gender = gender_id < (int)pokemon.gender()
                    ? GenderFilter::FEMALE
                    : GenderFilter::MALE;
    }

    //  Nature
    nature = static_cast<u8>(rng.nextInt(25, 31));

    std::stringstream ss;
    ss << tostr_hex_padded(seed)
       << " : Skips = " << tostr_commas(skips)
       << " - " << SHINY_TYPE[shiny]
       << " " << dump_IVs(IVs, characteristic)
       << " " << to_string((Nature)nature)
       << ", ";
    switch (ability){
    case 0:
        ss << "Ability 1";
        break;
    case 1:
        ss << "Ability 2";
        break;
    case 2:
        ss << "Ability H";
        break;
    }

    const char* gender_string;
    switch (gender){
    case GenderFilter::FEMALE:
        gender_string = " (female)";
        break;
    case GenderFilter::MALE:
        gender_string = " (male)";
        break;
    default:
        gender_string = " (genderless)";
    }
    ss << ", Gender #" << gender_id << gender_string;

    return ss.str();
}



void PrintReporter::report(uint64_t seed, uint64_t skips){
    std::cout << dump_seed(m_pokemon, seed, skips) << std::endl;
}



}
}
