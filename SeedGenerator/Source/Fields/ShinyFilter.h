
#pragma once
#ifndef SeedGenerator_ShinyFilter_H
#define SeedGenerator_ShinyFilter_H

#include <string>
namespace SeedGenerator{

class ShinyFilter{
    unsigned flag;

public:
    static const ShinyFilter NONE;
    static const ShinyFilter STAR;
    static const ShinyFilter SQUARE;
    static const ShinyFilter SHINY;
    static const ShinyFilter ALL;

    ShinyFilter(unsigned f) : flag(f) {}
    ShinyFilter(const std::string& token);

    operator bool() const{
        return flag != 0;
    }
    friend ShinyFilter operator|(ShinyFilter f0, ShinyFilter f1){
        return ShinyFilter(f0.flag | f1.flag);
    }
    friend ShinyFilter operator&(ShinyFilter f0, ShinyFilter f1){
        return ShinyFilter(f0.flag & f1.flag);
    }

    std::string to_string() const;
};


}
#endif
