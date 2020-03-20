
#include <algorithm>
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "Tools/Tools.h"
#include "DistantSearchSession.h"

#if 0
#elif ENABLE_17_AVX512
#include "TestShiny8_AVX512.h"
#elif ENABLE_13_AVX2
#include "TestShiny4_AVX2.h"
#elif ENABLE_07_SSE41
#include "TestShiny2_SSE41.h"
#endif
#include "TestSeed.h"

namespace SeedGenerator{
namespace DistantSearch{


DistantSearchSession::DistantSearchSession(
    const PokemonSpec& pokemon,
    const SearchFilter& filter,
    const SearchParameters& params,
    uint64_t odds
)
    : m_pokemon(pokemon)
    , m_filter(filter)
    , m_seed(params.seed())
    , m_frames(params.frames())
    , m_results(params.max_results())
    , m_current(0)
    , m_found(0)
    , m_workers(params.threads())
    , m_running(true)
{
    if (m_results == 0){
        m_results = (uint64_t)0 - 1;
    }
    m_block = odds / m_workers.size();
    m_block >>= 2;
    m_block = std::max(m_block, BLOCK_SIZE);

//    m_start_time = std::chrono::system_clock::now();
    for (std::thread& worker : m_workers){
        worker = std::thread(&DistantSearchSession::worker_thread, this);
    }
}
DistantSearchSession::~DistantSearchSession(){
    for (std::thread& worker : m_workers){
        worker.join();
    }
}

void DistantSearchSession::report(uint64_t seed, uint64_t skips){
    std::lock_guard<std::mutex> lg(m_lock);
    if (m_found == m_results){
        return;
    }
    std::cout << dump_seed(m_pokemon, seed, skips) << std::endl;
    m_found++;
    if (m_found == m_results){
        m_running.store(false, std::memory_order_release);
    }
}
uint64_t DistantSearchSession::select_block() const{
    if (m_current == m_frames){
        return 0;
    }
    uint64_t min_block = 1;
    uint64_t max_block = m_frames - m_current;

    uint64_t block = (max_block - 1) / m_workers.size() + 1;
    block = std::min(block, m_block);
    block = std::max(block, (uint64_t)BLOCK_SIZE);

    block = std::min(block, max_block);
    block = std::max(block, min_block);
    return block;
}

void DistantSearchSession::test_range(uint64_t start, uint64_t frames){
    while (frames > 0){
        if (!m_running.load(std::memory_order_acquire)){
            return;
        }

        size_t block = (size_t)std::min(frames, (uint64_t)BLOCK_SIZE);

#if 0
#elif ENABLE_17_AVX512
    test_seed_AVX512(*this, m_pokemon, m_filter, m_seed, start, block);
#elif ENABLE_13_AVX2
    test_seed_AVX2(*this, m_pokemon, m_filter, m_seed, start, block);
#elif ENABLE_07_SSE41
    test_seed_SSE41(*this, m_pokemon, m_filter, m_seed, start, block);
#else
    test_seed_Default(*this, m_pokemon, m_filter, m_seed, start, block);
#endif

        start += block;
        frames -= block;
    }
}

void DistantSearchSession::worker_thread(){
#ifdef _WIN32
    //  Avoid freezing the system on Windows with 100% CPU usage.
    SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);
#endif
    while (m_running.load(std::memory_order_acquire)){
        uint64_t index;
        uint64_t block;
        {
            std::lock_guard<std::mutex> lg(m_lock);
            block = select_block();
            index = m_current;
            m_current += block;
        }
        if (block == 0){
            break;
        }
        test_range(index, block);
    }
}



}
}

