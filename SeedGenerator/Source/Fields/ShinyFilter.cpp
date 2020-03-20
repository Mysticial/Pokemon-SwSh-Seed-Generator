
#include <vector>
#include <map>
#include <iostream>
#include "ShinyFilter.h"
namespace SeedGenerator{

const ShinyFilter ShinyFilter::NONE     = 1 << 0;
const ShinyFilter ShinyFilter::STAR     = 1 << 1;
const ShinyFilter ShinyFilter::SQUARE   = 1 << 2;
const ShinyFilter ShinyFilter::SHINY    = STAR | SQUARE;
const ShinyFilter ShinyFilter::ALL      = NONE | STAR | SQUARE;


std::string ShinyFilter::to_string() const{
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
        return "Unspecified";
    }
    std::string out;
    out += str[0];
    for (size_t c = 1; c < str.size(); c++){
        out += ", ";
        out += str[c];
    }
    return out;
}

const std::map<std::string, ShinyFilter> SHINY_FILTER_TOKENS{
    {"Unspecified", ShinyFilter::ALL},
    {"NotShiny",    ShinyFilter::NONE},
    {"AnyShiny",    ShinyFilter::SHINY},
    {"Star",        ShinyFilter::STAR},
    {"Square",      ShinyFilter::SQUARE},
};
ShinyFilter::ShinyFilter(const std::string& token){
    auto iter = SHINY_FILTER_TOKENS.find(token);
    if (iter == SHINY_FILTER_TOKENS.end()){
        throw "Invalid ShinyFilter: " + token;
    }
    *this = iter->second;
}

}
