
#include <map>
#include <iostream>
#include "Tools/Tools.h"
#include "SearchFilter.h"
using std::cout;
using std::endl;

namespace SeedGenerator{
namespace DistantSearch{

const std::map<std::string, void(*)(const char*&, SearchFilter&)> SEARCH_FILTER_KEYS{
    {"Shininess:",  SearchFilter::parse_shininess},
    {"IVs:",        SearchFilter::parse_IVs},
    {"Ability:",    SearchFilter::parse_ability},
    {"Nature:",     SearchFilter::parse_nature},
    {"Gender:",     SearchFilter::parse_gender},
};

void SearchFilter::parse_shininess(const char*& stream, SearchFilter& self){
    skip_whitespace(stream);
    std::string token = parse_token(stream);
    self.shiny = ShinySearchFilter(token);
}
void SearchFilter::parse_IVs(const char*& stream, SearchFilter& self){
    self.IVs = IvFilter(stream);
}
void SearchFilter::parse_ability(const char*& stream, SearchFilter& self){
    skip_whitespace(stream);
    std::string token = parse_token(stream);
    if (token == "Unspecified"){
        self.ability = -1;
        return;
    }
    if (token == "1"){
        self.ability = 0;
        return;
    }
    if (token == "2"){
        self.ability = 1;
        return;
    }
    if (token == "H"){
        self.ability = 2;
        return;
    }
    throw "Invalid Ability: " + token;
}
void SearchFilter::parse_gender(const char*& stream, SearchFilter& self){
    skip_whitespace(stream);
    std::string token = parse_token(stream);
    self.gender = read_gender(token);
}
void SearchFilter::parse_nature(const char*& stream, SearchFilter& self){
    skip_whitespace(stream);
    std::string token = parse_token(stream);
    self.nature = read_nature(token);
}

SearchFilter::SearchFilter(std::istream& stream){
    std::string line;
    while (std::getline(stream, line)){
        if (line.empty()){
            return;
        }
        const char* str = line.c_str();
        skip_whitespace(str);
        std::string token = parse_token(str);
        if (token.empty()){
            continue;
        }

        auto iter = SEARCH_FILTER_KEYS.find(token);
        if (iter == SEARCH_FILTER_KEYS.end()){
            throw "Unrecognized Token: " + token;
        }

        if (iter->second == nullptr){
            continue;
        }
        iter->second(str, *this);
    }
}


void SearchFilter::print() const{
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
            cout << (int)IVs[c];
        }
        if (c == IVs.characteristic()){
            cout << "*";
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

    cout << "    Nature:     " << to_string(nature) << endl;

    cout << "    Gender:     ";
    switch (gender){
    case GenderFilter::FEMALE:
        cout << "Female";
        break;
    case GenderFilter::MALE:
        cout << "Male";
        break;
    case GenderFilter::UNSPECIFIED:
        cout << "Unspecified";
        break;
    }
    cout << endl;

    cout << endl;
}



}
}
