
#pragma once
#ifndef SeedGenerator_CalculateSeedParameters_H
#define SeedGenerator_CalculateSeedParameters_H

#include "Fields/Types.h"
#include "Fields/IvFilter.h"
namespace SeedGenerator{
namespace SeedCalculator{

class CalculateSeedParameters{
public:
    CalculateSeedParameters() = default;
    CalculateSeedParameters(std::istream& stream);

//    ShinyType   shiny   () const{ return m_shiny; }
    uint32_t    ec      () const{ return m_ec; }
    uint32_t    pid     () const{ return m_pid; }
    IvFilter    IVs     () const{ return m_IVs; }

    void print();

public:
//    static void parse_shiny (const char*& stream, CalculateSeedParameters& self);
    static void parse_ec    (const char*& stream, CalculateSeedParameters& self);
    static void parse_pid   (const char*& stream, CalculateSeedParameters& self);
    static void parse_IVs   (const char*& stream, CalculateSeedParameters& self);

private:
//    ShinyType m_shiny = ShinyType::NONE;
    uint32_t m_ec = 0;
    uint32_t m_pid = 0;
    IvFilter m_IVs;
};



}
}
#endif
