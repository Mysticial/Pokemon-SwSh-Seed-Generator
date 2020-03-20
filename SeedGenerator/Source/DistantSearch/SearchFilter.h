
#pragma once
#ifndef SeedGenerator_SearchFilter_H
#define SeedGenerator_SearchFilter_H

#include <fstream>
#include "Fields/Gender.h"
#include "Fields/Nature.h"
#include "Fields/ShinyFilter.h"
#include "Fields/IvFilter.h"
namespace SeedGenerator{
namespace DistantSearch{

class SearchFilter{
public:
    SearchFilter() = default;
    SearchFilter(std::istream& stream);
    void print() const;

public:
    static void parse_shininess (const char*& stream, SearchFilter& self);
    static void parse_IVs       (const char*& stream, SearchFilter& self);
    static void parse_ability   (const char*& stream, SearchFilter& self);
    static void parse_gender    (const char*& stream, SearchFilter& self);
    static void parse_nature    (const char*& stream, SearchFilter& self);

public:
    ShinyFilter shiny   = ShinyFilter::SHINY;
    IvFilter IVs;
    char ability        = -1;
    Nature nature       = Nature::UNSPECIFIED;
    GenderFilter gender = GenderFilter::UNSPECIFIED;
};


}
}
#endif
