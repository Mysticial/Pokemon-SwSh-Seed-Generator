
#pragma once
#ifndef SeedGenerator_Types_H
#define SeedGenerator_Types_H
namespace SeedGenerator{


enum class ShinyType{
    NONE    = 0,
    STAR    = 1,
    SQUARE  = 2,
};
const char* SHINY_TYPE[];


enum class Ability{
    HIDDEN,
    NO_HIDDEN,
    LOCKED,
};


}
#endif
