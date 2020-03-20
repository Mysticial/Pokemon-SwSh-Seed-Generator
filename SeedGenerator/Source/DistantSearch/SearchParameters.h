
#pragma once
#ifndef SeedGenerator_SearchParameters_H
#define SeedGenerator_SearchParameters_H

#include <stdint.h>
#include <fstream>
namespace SeedGenerator{
namespace DistantSearch{


class SearchParameters{
public:
    SearchParameters();
    SearchParameters(std::istream& stream);
    void print() const;

    uint64_t    seed        () const{ return m_seed; }
    uint64_t    max_results () const{ return m_max_results; }
    uint64_t    frames      () const{ return m_frames; }
    size_t      threads     () const{ return m_threads; }

public:
    static void parse_seed      (const char*& stream, SearchParameters& self);
    static void parse_results   (const char*& stream, SearchParameters& self);
    static void parse_frames    (const char*& stream, SearchParameters& self);

private:
    uint64_t m_seed = 0;
    uint64_t m_max_results = 100;
    uint64_t m_frames = 1'000'000'000'000;
    size_t m_threads;
};


}
}
#endif
