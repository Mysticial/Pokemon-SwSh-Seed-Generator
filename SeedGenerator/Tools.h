
#include <mutex>
#include <iostream>
#include "XoroShiro.h"
using namespace std;

enum class Shiny{
    NONE,
    STAR,
    SQUARE,
    UNSPECIFIED,
};
const char* SHINY[] = {
    "No    ",
    "Star  ",
    "Square",
};

enum class Ability{
    HIDDEN,
    NO_HIDDEN,
    LOCKED,
};

enum class Nature{
    Hardy,
    Lonely,
    Brave,
    Adamant,
    Naughty,
    Bold,
    Docile,
    Relaxed,
    Impish,
    Lax,
    Timid,
    Hasty,
    Serious,
    Jolly,
    Naive,
    Modest,
    Mild,
    Quiet,
    Bashful,
    Rash,
    Calm,
    Gentle,
    Sassy,
    Careful,
    Quirky,
    UNSPECIFIED,
};
const char* NATURES[] = {
    "Hardy",
    "Lonely",
    "Brave",
    "Adamant",
    "Naughty",
    "Bold",
    "Docile",
    "Relaxed",
    "Impish",
    "Lax",
    "Timid",
    "Hasty",
    "Serious",
    "Jolly",
    "Naive",
    "Modest",
    "Mild",
    "Quiet",
    "Bashful",
    "Rash",
    "Calm",
    "Gentle",
    "Sassy",
    "Careful",
    "Quirky",
};


struct Pokemon{
    Ability ability;
    int max_ivs;
    bool gendered;
};



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

struct Filter{
    Shiny shiny = Shiny::UNSPECIFIED;
    int IVs[6] = {-1, -1, -1, -1, -1, -1};
    int ability = -1;
    Nature nature = Nature::UNSPECIFIED;
};

std::mutex print;

void test_seed(const Pokemon& pokemon, const Filter& filter, u64 seed, u64 skips){
    int shiny = 0;
    int IVs[6] = {-1, -1, -1, -1, -1, -1};
    int ability = -1;
    int gender = -1;
    int nature;

    seed += skips * 0x82A2B175229D6A5B;

    XoroShiro rng(seed);

    u32 ec = rng.nextInt(0xffffffff, 0xffffffff);

    u32 sidtid = rng.nextInt(0xffffffff, 0xffffffff);
    u32 pid = rng.nextInt(0xffffffff, 0xffffffff);

    u16 ftsv = getSv(sidtid);
    u16 psv = getSv(pid);

    if (ftsv == psv){
        shiny = getShinyType(sidtid, pid);
//        cout << "Shiny = " << shiny << endl;
    }
    if (filter.shiny != Shiny::UNSPECIFIED && (Shiny)shiny != filter.shiny){
        return;
    }

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
        if (IVs[i] == -1)
        {
            IVs[i] = static_cast<u8>(rng.nextInt(31));
        }
//        cout << "IV = " << IVs[i] << endl;
        int filters = filter.IVs[i];
        if (filters != -1 && IVs[i] != filters){
            return;
        }
    }

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

    if (pokemon.gendered){
        gender = static_cast<u8>(rng.nextInt(253, 255) + 1);
    }
//    cout << "Gender = " << gender << endl;

    nature = static_cast<u8>(rng.nextInt(25, 31));
    if (filter.nature != Nature::UNSPECIFIED && (Nature)nature != filter.nature){
        return;
    }
//    cout << "Nature = " << NATURES[nature] << endl;

    std::lock_guard<std::mutex> lg(print);
    cout << std::hex << seed << std::dec
         << " : Skips = " << skips
         << " - " << SHINY[shiny]
         << " {" << IVs[0]
         << ", " << IVs[1]
         << ", " << IVs[2]
         << ", " << IVs[3]
         << ", " << IVs[4]
         << ", " << IVs[5]
         << "}  " << NATURES[nature]
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
    cout << ", Gender #" << gender << endl;
}
