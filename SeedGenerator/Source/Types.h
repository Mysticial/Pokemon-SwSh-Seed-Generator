
#pragma once
#ifndef SeedGenerator_Types_H
#define SeedGenerator_Types_H

#include <string>
#include <vector>
#include <iostream>
using std::cout;
using std::endl;

enum class ShinyType{
    NONE,
    STAR,
    SQUARE,
};
const char* SHINY_TYPE[] = {
    "No    ",
    "Star  ",
    "Square",
};

class ShinyFilter{
    unsigned flag;

public:
    static const ShinyFilter NONE;
    static const ShinyFilter STAR;
    static const ShinyFilter SQUARE;
    static const ShinyFilter SHINY;
    static const ShinyFilter ALL;

    ShinyFilter(unsigned f) : flag(f) {}

    operator bool() const{
        return flag != 0;
    }
    friend ShinyFilter operator|(ShinyFilter f0, ShinyFilter f1){
        return ShinyFilter(f0.flag | f1.flag);
    }
    friend ShinyFilter operator&(ShinyFilter f0, ShinyFilter f1){
        return ShinyFilter(f0.flag & f1.flag);
    }

    std::string to_string() const{
        std::vector<const char*> str;
        if (*this & NONE){
            str.emplace_back("Not Shiny");
        }
        if (*this & STAR){
            str.emplace_back("Star");
        }
        if (*this & SQUARE){
            str.emplace_back("Square");
        }
        if (str.size() == 0){
            return "None Selected";
        }
        std::string out;
        out += str[0];
        for (size_t c = 1; c < str.size(); c++){
            out += ", ";
            out += str[c];
        }
        return out;
    }
};
const ShinyFilter ShinyFilter::NONE     = 1 << 0;
const ShinyFilter ShinyFilter::STAR     = 1 << 1;
const ShinyFilter ShinyFilter::SQUARE   = 1 << 2;
const ShinyFilter ShinyFilter::SHINY    = STAR | SQUARE;
const ShinyFilter ShinyFilter::ALL      = NONE | STAR | SQUARE;




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

enum class GenderRatio{
    MALE        = 0,
    MALE_88     = 31,
    MALE_75     = 63,
    EVEN        = 127,
    FEMALE_75   = 191,
    FEMALE_88   = 225,
    FEMALE      = 254,
    GENDERLESS  = 255,
};

enum class Gender{
    FEMALE      = 0,
    MALE        = 1,
    UNSPECIFIED = 2,
};

struct Pokemon{
    Ability ability = Ability::HIDDEN;
    int max_ivs = 4;
    GenderRatio gender = GenderRatio::EVEN;

    void print() const{
        cout << "Pokemon Spec:" << endl;
        switch (ability){
        case Ability::HIDDEN: cout << "    Ability:    hidden possible" << endl;
            break;
        case Ability::NO_HIDDEN:
            cout << "    Ability:    hidden not possible" << endl;
            break;
        case Ability::LOCKED:
            cout << "    Ability:    locked" << endl;
            break;
        }

        cout << "    Max IVs:    " << max_ivs << endl;

        switch (gender){
        case GenderRatio::MALE:
            cout << "    Gender:     100% Male" << endl;
            break;
        case GenderRatio::MALE_88:
            cout << "    Gender:     88% Male" << endl;
            break;
        case GenderRatio::MALE_75:
            cout << "    Gender:     75% Male" << endl;
            break;
        case GenderRatio::EVEN:
            cout << "    Gender:     50% male/female" << endl;
            break;
        case GenderRatio::FEMALE_75:
            cout << "    Gender:     75% female" << endl;
            break;
        case GenderRatio::FEMALE_88:
            cout << "    Gender:     88% female" << endl;
            break;
        case GenderRatio::FEMALE:
            cout << "    Gender:     100% female" << endl;
            break;
        case GenderRatio::GENDERLESS:
            cout << "    Gender:     genderless" << endl;
            break;
        }
        cout << endl;
    }
};

struct Filter{
    ShinyFilter shiny   = ShinyFilter::STAR | ShinyFilter::SQUARE;
    int IVs[6]          = {-1, -1, -1, -1, -1, -1};
    int ability         = -1;
    Nature nature       = Nature::UNSPECIFIED;
    Gender gender       = Gender::UNSPECIFIED;

    void print() const{
        cout << "Desired Stats:" << endl;
        cout << "    Shiny:      " << shiny.to_string() << endl;

        cout << "    IVs:        {";
        for (size_t c = 0; c < 6; c++){
            if (c != 0){
                cout << ", ";
            }
            if (IVs[c] < 0){
                cout << "x";
            }else{
                cout << IVs[c];
            }
        }
        cout << "}" << endl;

        cout << "    Ability:    ";
        switch (ability){
        case -1:
            cout << "Unspecified";
            break;
        case 0:
            cout << "Slot 1";
            break;
        case 1:
            cout << "Slot 2";
            break;
        case 2:
            cout << "Hidden";
            break;
        }
        cout << endl;

        if (nature != Nature::UNSPECIFIED){
            cout << "    Nature:     " << NATURES[(int)nature] << endl;
        }

        cout << "    Gender:     ";
        switch (gender){
        case Gender::FEMALE:
            cout << "Female";
            break;
        case Gender::MALE:
            cout << "Male";
            break;
        case Gender::UNSPECIFIED:
            cout << "Unspecified";
            break;
        }
        cout << endl;

        cout << endl;
    }
};


std::string tostr_commas(uint64_t x){
    //  Prints out x with comma separators.

    std::string str = std::to_string(x);
    std::string out;

    const char* ptr = str.c_str();
    size_t len = str.size();

    size_t commas = (len + 2) / 3 - 1;
    size_t shift = len - commas * 3;

    while (1){
        char ch = *ptr++;
        if (ch == '\0')
            break;
        if (shift == 0){
            out += ',';
            shift = 3;
        }
        out += ch;
        shift--;
    }

    return out;
}

#endif
