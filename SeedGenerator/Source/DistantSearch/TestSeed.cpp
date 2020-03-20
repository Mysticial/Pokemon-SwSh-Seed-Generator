
#include <sstream>
#include "Tools/Tools.h"
#include "Tools/XoroShiro.h"
#include "TestSeed.h"
namespace SeedGenerator{
namespace DistantSearch{


void test_seed(
    SeedReporter& reporter,
    const PokemonSpec& pokemon,
    const SearchFilter& filter,
    uint64_t seed, uint64_t skips
){

    seed += skips * 0x82A2B175229D6A5B;

    XoroShiro rng(seed);

    u32 ec = rng.nextInt(0xffffffff);

    u32 sidtid = rng.nextInt(0xffffffff);
    u32 pid = rng.nextInt(0xffffffff);

//    cout << pid << endl;

    u16 ftsv = getSv(sidtid);
    u16 psv = getSv(pid);

    int shiny = 0;
    if (ftsv == psv){
        shiny = getShinyType(sidtid, pid);
//        cout << "Shiny = " << shiny << endl;
    }
    if (!(ShinyFilter(1 << shiny) & filter.shiny)){
        return;
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
        int filters = filter.IVs[i];
        if (filters != -1 && IVs[i] != filters){
            return;
        }
    }

    //  Characteristic
    characteristic = getCharacteristic(ec, IVs);
    if (filter.IVs.characteristic() != -1 && filter.IVs.characteristic() != characteristic){
        return;
    }

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
    if (filter.ability != -1 && ability != filter.ability){
        return;
    }
//    cout << "Ability = " << ability << endl;

//    cout << "Gender = " << gender << endl;
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

    if (filter.gender != GenderFilter::UNSPECIFIED && gender != filter.gender){
        return;
    }

    nature = static_cast<u8>(rng.nextInt(25, 31));
    if (filter.nature != Nature::UNSPECIFIED && (Nature)nature != filter.nature){
        return;
    }
//    cout << "Nature = " << NATURES[nature] << endl;

#if 0
    std::lock_guard<std::mutex> lg(print);
    cout << std::hex << seed << std::dec
         << " : Skips = " << tostr_commas(skips)
         << " - " << SHINY_TYPE[shiny]
         << " {" << (int)IVs[0] << (characteristic == 0 ? "*" : "")
         << ", " << (int)IVs[1] << (characteristic == 1 ? "*" : "")
         << ", " << (int)IVs[2] << (characteristic == 2 ? "*" : "")
         << ", " << (int)IVs[3] << (characteristic == 3 ? "*" : "")
         << ", " << (int)IVs[4] << (characteristic == 4 ? "*" : "")
         << ", " << (int)IVs[5] << (characteristic == 5 ? "*" : "")
         << "} " << to_string((Nature)nature)
         << ", ";
    switch (ability){
    case 0:
        cout << "Ability 1";
        break;
    case 1:
        cout << "Ability 2";
        break;
    case 2:
        cout << "Ability H";
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
    cout << ", Gender #" << gender_id << gender_string << endl;
#endif
    reporter.report(seed, skips);
}


void test_seed_Default(
    SeedReporter& reporter,
    const PokemonSpec& pokemon,
    const SearchFilter& filter,
    uint64_t seed, uint64_t skips,
    uint64_t iterations
){
    for (uint64_t c = 0; c < iterations; c++){
        test_seed(reporter, pokemon, filter, seed, skips + c);
    }
}



}
}
