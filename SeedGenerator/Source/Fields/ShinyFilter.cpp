
#include <vector>
#include <map>
#include <iostream>
#include "ShinyFilter.h"
namespace SeedGenerator{

const std::map<std::string, ShinyTypeInput> SHINY_TYPE_INPUT_TOKENS{
    {"Unspecified",     ShinyTypeInput::UNSPECIFIED},
    {"UnknownShiny",    ShinyTypeInput::UNKNOWN_SHINY},
    {"NotShiny",        ShinyTypeInput::NOT_SHINY},
    {"Star",            ShinyTypeInput::STAR},
    {"Square",          ShinyTypeInput::SQUARE},
};
ShinyTypeInput parse_ShinyTypeInput(const std::string& token){
    auto iter = SHINY_TYPE_INPUT_TOKENS.find(token);
    if (iter == SHINY_TYPE_INPUT_TOKENS.end()){
        throw "Invalid ShinySearchFilter: " + token;
    }
    return iter->second;
}
std::string to_string(ShinyTypeInput type){
    switch (type){
    case ShinyTypeInput::UNSPECIFIED:
        return "Unspecified";
    case ShinyTypeInput::UNKNOWN_SHINY:
        return "Unknown Shiny";
    case ShinyTypeInput::NOT_SHINY:
        return "Not Shiny";
    case ShinyTypeInput::STAR:
        return "Star";
    case ShinyTypeInput::SQUARE:
        return "Square";
    }
    throw "Invalid Shiny Type";
}













const ShinySearchFilter ShinySearchFilter::NONE     = 1 << 0;
const ShinySearchFilter ShinySearchFilter::STAR     = 1 << 1;
const ShinySearchFilter ShinySearchFilter::SQUARE   = 1 << 2;
const ShinySearchFilter ShinySearchFilter::SHINY    = STAR | SQUARE;
const ShinySearchFilter ShinySearchFilter::ALL      = NONE | STAR | SQUARE;


std::string ShinySearchFilter::to_string() const{
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

const std::map<std::string, ShinySearchFilter> SHINY_FILTER_TOKENS{
    {"Unspecified", ShinySearchFilter::ALL},
    {"NotShiny",    ShinySearchFilter::NONE},
    {"AnyShiny",    ShinySearchFilter::SHINY},
    {"Star",        ShinySearchFilter::STAR},
    {"Square",      ShinySearchFilter::SQUARE},
};
ShinySearchFilter::ShinySearchFilter(const std::string& token){
    auto iter = SHINY_FILTER_TOKENS.find(token);
    if (iter == SHINY_FILTER_TOKENS.end()){
        throw "Invalid ShinySearchFilter: " + token;
    }
    *this = iter->second;
}

}
