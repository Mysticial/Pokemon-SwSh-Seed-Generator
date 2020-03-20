
#include <map>
#include "Gender.h"
namespace SeedGenerator{


std::string to_string(GenderRatio ratio){
    switch (ratio){
    case GenderRatio::MALE:
        return "100% Male";
    case GenderRatio::MALE_88:
        return "88% Male";
    case GenderRatio::MALE_75:
        return "75% Male";
    case GenderRatio::EVEN:
        return "50% male/female";
    case GenderRatio::FEMALE_75:
        return "75% female";
    case GenderRatio::FEMALE_88:
        return "88% female";
    case GenderRatio::FEMALE:
        return "100% female";
    case GenderRatio::GENDERLESS:
        return "genderless";
    default:
        throw "Invalid Gender";
    }
}

const std::map<std::string, GenderRatio> GENDER_RATIO_TOKENS{
    {"MALE",        GenderRatio::MALE},
    {"MALE_88",     GenderRatio::MALE_88},
    {"MALE_75",     GenderRatio::MALE_75},
    {"EVEN",        GenderRatio::EVEN},
    {"FEMALE_75",   GenderRatio::FEMALE_75},
    {"FEMALE_88",   GenderRatio::FEMALE_88},
    {"FEMALE",      GenderRatio::FEMALE},
    {"GENDERLESS",  GenderRatio::GENDERLESS},
};
GenderRatio read_genderratio(const std::string& token){
    auto iter = GENDER_RATIO_TOKENS.find(token);
    if (iter == GENDER_RATIO_TOKENS.end()){
        throw "Invalid GenderRatio: " + token;
    }
    return iter->second;
}

const std::map<std::string, GenderFilter> GENDER_FILTER_TOKENS{
    {"Unspecified", GenderFilter::UNSPECIFIED},
    {"Male",        GenderFilter::MALE},
    {"Female",      GenderFilter::FEMALE},
};
GenderFilter read_gender(const std::string& token){
    auto iter = GENDER_FILTER_TOKENS.find(token);
    if (iter == GENDER_FILTER_TOKENS.end()){
        throw "Invalid GenderFilter: " + token;
    }
    return iter->second;
}


}
