
#pragma once
#ifndef SeedGenerator_Gender_H
#define SeedGenerator_Gender_H

#include <string>
namespace SeedGenerator{


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

enum class GenderFilter{
    FEMALE      = 0,
    MALE        = 1,
    UNSPECIFIED = 2,
};

std::string to_string(GenderRatio ratio);
GenderRatio read_genderratio(const std::string& token);
GenderFilter read_gender(const std::string& token);



}
#endif
