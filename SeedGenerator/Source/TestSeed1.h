
#pragma once
#ifndef SeedGenerator_TestSeed1_H
#define SeedGenerator_TestSeed1_H

#include <string>
#include <mutex>
#include "XoroShiro.h"
#include "Types.h"


static inline u16 getSv(u32 val)
{
    return ((val >> 16) ^ (val & 0xFFFF)) >> 4;
}

static inline u8 getShinyType(u32 sidtid, u32 pid)
{
    u16 val = (sidtid ^ pid) >> 16;
    if ((val ^ (sidtid & 0xffff)) == (pid & 0xffff))
    {
        return 2; // Square shiny
    }

    return 1; // Star shiny
}

static inline char getCharacteristic(u32 ec, const char ivs[6]){
    const u8 statOrder[6] = { 0, 1, 2, 5, 3, 4 };

    u8 charStat = ec % 6;
    for (u8 i = 0; i < 6; i++)
    {
        u8 stat = statOrder[(charStat + i) % 6];
        if (ivs[stat] == 31)
        {
            return stat;
        }
    }
    return statOrder[charStat];
}


std::mutex print;

void test_seed(const Pokemon& pokemon, const Filter& filter, u64 seed, u64 skips){

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
    for (u8 i = 0; i < pokemon.max_ivs;){
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
    if (filter.characteristic != -1 && filter.characteristic != characteristic){
        return;
    }

    //  Ability
    switch (pokemon.ability){
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
    Gender gender;
    switch (pokemon.gender){
    case GenderRatio::GENDERLESS:
        gender = Gender::UNSPECIFIED;
        break;
    case GenderRatio::FEMALE:
        gender = Gender::FEMALE;
        break;
    case GenderRatio::MALE:
        gender = Gender::MALE;
        break;
    default:
        gender_id = static_cast<u8>(rng.nextInt(253, 255) + 1);
        gender = gender_id < (int)pokemon.gender
                    ? Gender::FEMALE
                    : Gender::MALE;
    }

    if (filter.gender != Gender::UNSPECIFIED && gender != filter.gender){
        return;
    }

    nature = static_cast<u8>(rng.nextInt(25, 31));
    if (filter.nature != Nature::UNSPECIFIED && (Nature)nature != filter.nature){
        return;
    }
//    cout << "Nature = " << NATURES[nature] << endl;

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
         << "} " << NATURES[nature]
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
    case Gender::FEMALE:
        gender_string = " (female)";
        break;
    case Gender::MALE:
        gender_string = " (male)";
        break;
    default:
        gender_string = " (genderless)";
    }
    cout << ", Gender #" << gender_id << gender_string << endl;
}

#endif
