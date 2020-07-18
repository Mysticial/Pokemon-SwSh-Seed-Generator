
#pragma once
#ifndef SeedGenerator_ShinyFilter_H
#define SeedGenerator_ShinyFilter_H

#include <string>
namespace SeedGenerator{

enum class ShinyTypeInput{
    UNSPECIFIED,
    UNKNOWN_SHINY,
    NOT_SHINY,
    STAR,
    SQUARE,
};

ShinyTypeInput parse_ShinyTypeInput(const std::string& token);
std::string to_string(ShinyTypeInput type);




class ShinySearchFilter{
    unsigned flag;

public:
    static const ShinySearchFilter NONE;
    static const ShinySearchFilter STAR;
    static const ShinySearchFilter SQUARE;
    static const ShinySearchFilter SHINY;
    static const ShinySearchFilter ALL;

    ShinySearchFilter(unsigned f) : flag(f) {}
    ShinySearchFilter(const std::string& token);

    explicit operator bool() const{
        return flag != 0;
    }
    friend ShinySearchFilter operator|(ShinySearchFilter f0, ShinySearchFilter f1){
        return ShinySearchFilter(f0.flag | f1.flag);
    }
    friend ShinySearchFilter operator&(ShinySearchFilter f0, ShinySearchFilter f1){
        return ShinySearchFilter(f0.flag & f1.flag);
    }

    std::string to_string() const;
};


}
#endif
