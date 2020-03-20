
#pragma once
#ifndef SeedGenerator_DistantSearchSession_H
#define SeedGenerator_DistantSearchSession_H

#include <vector>
//#include <chrono>
#include <atomic>
#include <mutex>
#include "SeedPrinter.h"
#include "PokemonSpec.h"
#include "SearchFilter.h"
#include "SearchParameters.h"
namespace SeedGenerator{
namespace DistantSearch{

class DistantSearchSession : public SeedReporter{
    static const uint64_t BLOCK_SIZE = 1048576;

public:
    DistantSearchSession(
        const PokemonSpec& pokemon,
        const SearchFilter& filter,
        const SearchParameters& params,
        uint64_t odds   //  Used by scheduler to make search results "more in order".
    );
    ~DistantSearchSession();

private:
    virtual void report(uint64_t seed, uint64_t skips) override;

    uint64_t select_block() const;
    void test_range(uint64_t start, uint64_t frames);
    void worker_thread();

private:
    const PokemonSpec& m_pokemon;
    const SearchFilter& m_filter;
    uint64_t m_seed;
    uint64_t m_frames;
    uint64_t m_results;
    uint64_t m_block;

    std::mutex m_lock;
//    std::chrono::time_point<std::chrono::system_clock> m_start_time;
    uint64_t m_current;
    uint64_t m_found;

    std::vector<std::thread> m_workers;
    std::atomic<bool> m_running;
};

}
}
#endif
