
#pragma once
#ifndef SeedGenerator_CalculateSeedParameters_H
#define SeedGenerator_CalculateSeedParameters_H

#include "Fields/Types.h"
#include "Fields/IvFilter.h"
#include "Fields/ShinyFilter.h"
namespace SeedGenerator{
namespace SeedCalculator{

class CalculateSeedParameters{
public:
    CalculateSeedParameters() = default;
    CalculateSeedParameters(std::istream& stream);

    uint32_t        ec      () const{ return m_ec; }
    uint32_t        pid     () const{ return m_pid; }
    IvFilter        IVs     () const{ return m_IVs; }
    ShinyTypeInput  shiny   () const{ return m_shiny; }
//    int             tid     () const{ return m_tid; }
//    int             sid     () const{ return m_sid; }
//    uint32_t        fid     () const{ return m_fid; }

    void print();

public:
    static void parse_shiny (const char*& stream, CalculateSeedParameters& self);
    static void parse_ec    (const char*& stream, CalculateSeedParameters& self);
    static void parse_pid   (const char*& stream, CalculateSeedParameters& self);
    static void parse_IVs   (const char*& stream, CalculateSeedParameters& self);
//    static void parse_tid   (const char*& stream, CalculateSeedParameters& self);
//    static void parse_sid   (const char*& stream, CalculateSeedParameters& self);

private:
    uint32_t m_ec = 0;
    uint32_t m_pid = 0;
    IvFilter m_IVs;
    ShinyTypeInput m_shiny = ShinyTypeInput::UNSPECIFIED;
//    int m_tid = -1;
//    int m_sid = -1;
//    uint32_t m_fid = 0;
};



}
}
#endif
