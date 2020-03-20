
#pragma once
#ifndef SeedGenerator_Nature_H
#define SeedGenerator_Nature_H

#include <string>
namespace SeedGenerator{


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

std::string to_string(Nature nature);
Nature read_nature(const std::string& token);


}
#endif
