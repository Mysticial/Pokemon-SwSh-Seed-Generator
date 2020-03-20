
#include <map>
#include <thread>
#include <iostream>
#include "Tools/Tools.h"
#include "SearchParameters.h"
using std::cout;
using std::endl;

namespace SeedGenerator{
namespace DistantSearch{

const std::map<std::string, void(*)(const char*&, SearchParameters&)> SEARCH_PARAMETER_KEYS{
    {"StartingSeed:",   SearchParameters::parse_seed},
    {"MaxResults:",     SearchParameters::parse_results},
    {"MaxFrames:",      SearchParameters::parse_frames},
};

void SearchParameters::parse_seed(const char*& stream, SearchParameters& self){
    skip_whitespace(stream);
    std::string token = parse_token(stream);
    const char* str = token.c_str();
    self.m_seed = parse_hex(str);
}
void SearchParameters::parse_results(const char*& stream, SearchParameters& self){
    skip_whitespace(stream);
    std::string token = parse_token(stream);
    const char* str = token.c_str();
    self.m_max_results = parse_dec(str);
}
void SearchParameters::parse_frames(const char*& stream, SearchParameters& self){
    skip_whitespace(stream);
    std::string token = parse_token(stream);
    const char* str = token.c_str();
    self.m_frames = parse_dec(str);
}

SearchParameters::SearchParameters()
    : m_threads(std::thread::hardware_concurrency())
{}
SearchParameters::SearchParameters(std::istream& stream)
    : m_threads(std::thread::hardware_concurrency())
{
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

        auto iter = SEARCH_PARAMETER_KEYS.find(token);
        if (iter == SEARCH_PARAMETER_KEYS.end()){
            throw "Unrecognized Token: " + token;
        }

        if (iter->second == nullptr){
            continue;
        }
        iter->second(str, *this);
    }
}
void SearchParameters::print() const{
    cout << "Search Parameters:" << endl;
    cout << "    Starting Seed:  " << tostr_hex_padded(m_seed) << endl;
    cout << "    Max Results:    " << (m_max_results == 0 ? "Unlimited" : tostr_commas(m_max_results)) << endl;
    cout << "    Max Frames:     " << tostr_commas(m_frames) << endl;
#if 0
#elif ENABLE_17_AVX512
    cout << "    Arch:           AVX512" << endl;
#elif ENABLE_13_AVX2
    cout << "    Arch:           AVX2" << endl;
#elif ENABLE_07_SSE41
    cout << "    Arch:           SSE4.1" << endl;
#else
    cout << "    Arch:           Default" << endl;
#endif
    cout << "    Threads:        " << tostr_commas(m_threads) << endl;
    cout << endl;
}



}
}
