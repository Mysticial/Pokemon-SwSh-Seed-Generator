
#include <map>
#include "Nature.h"
namespace SeedGenerator{

//std::map<Nature, std::string> NATURE_ENUM_TOKENS{
//    {Nature::Hardy,         "Hardy"},
//    {Nature::Lonely,        "Lonely"},
//    {Nature::Brave,         "Brave"},
//    {Nature::Adamant,       "Adamant"},
//    {Nature::Naughty,       "Naughty"},
//    {Nature::Bold,          "Bold"},
//    {Nature::Docile,        "Docile"},
//    {Nature::Relaxed,       "Relaxed"},
//    {Nature::Impish,        "Impish"},
//    {Nature::Lax,           "Lax"},
//    {Nature::Timid,         "Timid"},
//    {Nature::Hasty,         "Hasty"},
//    {Nature::Serious,       "Serious"},
//    {Nature::Jolly,         "Jolly"},
//    {Nature::Naive,         "Naive"},
//    {Nature::Modest,        "Modest"},
//    {Nature::Mild,          "Mild"},
//    {Nature::Quiet,         "Quiet"},
//    {Nature::Bashful,       "Bashful"},
//    {Nature::Rash,          "Rash"},
//    {Nature::Calm,          "Calm"},
//    {Nature::Gentle,        "Gentle"},
//    {Nature::Sassy,         "Sassy"},
//    {Nature::Careful,       "Careful"},
//    {Nature::Quirky,        "Quirky"},
//    {Nature::UNSPECIFIED,   "Unspecified"},
//};
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
    "Unspecified",
};
std::string to_string(Nature nature){
    if ((int)nature > (int)Nature::UNSPECIFIED){
        throw "Invalid Nature.";
    }
    return NATURES[(int)nature];
}



const std::map<std::string, Nature> NATURE_ENUM_TOKENS{
    {"Hardy",       Nature::Hardy},
    {"Lonely",      Nature::Lonely},
    {"Brave",       Nature::Brave},
    {"Adamant",     Nature::Adamant},
    {"Naughty",     Nature::Naughty},
    {"Bold",        Nature::Bold},
    {"Docile",      Nature::Docile},
    {"Relaxed",     Nature::Relaxed},
    {"Impish",      Nature::Impish},
    {"Lax",         Nature::Lax},
    {"Timid",       Nature::Timid},
    {"Hasty",       Nature::Hasty},
    {"Serious",     Nature::Serious},
    {"Jolly",       Nature::Jolly},
    {"Naive",       Nature::Naive},
    {"Modest",      Nature::Modest},
    {"Mild",        Nature::Mild},
    {"Quiet",       Nature::Quiet},
    {"Bashful",     Nature::Bashful},
    {"Rash",        Nature::Rash},
    {"Calm",        Nature::Calm},
    {"Gentle",      Nature::Gentle},
    {"Sassy",       Nature::Sassy},
    {"Careful",     Nature::Careful},
    {"Quirky",      Nature::Quirky},
    {"Unspecified", Nature::UNSPECIFIED},
};
Nature read_nature(const std::string& token){
    auto iter = NATURE_ENUM_TOKENS.find(token);
    if (iter == NATURE_ENUM_TOKENS.end()){
        throw "Invalid GenderFilter: " + token;
    }
    return iter->second;
}


}
