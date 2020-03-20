
#include <iostream>
#include "DistantSearch/OddsCalculator.h"
#include "DistantSearchSession.h"
#include "DistantSearch.h"
using std::cout;
using std::endl;

namespace SeedGenerator{
namespace DistantSearch{

void distant_search(std::istream& stream){
    PokemonSpec pokemon;
    SearchFilter filter;
    SearchParameters params;

    std::string line;
    while (std::getline(stream, line)){
        if (line.empty()){
            continue;
        }
        if (line == "PokemonSpec:"){
            pokemon = PokemonSpec(stream);
            continue;
        }
        if (line == "SearchFilter:"){
            filter = SearchFilter(stream);
            continue;
        }
        if (line == "SearchParameters:"){
            params = SearchParameters(stream);
            continue;
        }
    }

    //  Perform search.
//    search(pokemon, filter, params);

    pokemon.print();
    filter.print();
    uint64_t odds;
    try{
        odds = print_odds(pokemon, filter);
    }catch (const char* str){
        cout << endl;
        cout << str << endl;
        cout << "Canceling Search..." << endl;
        cout << endl;
        return;
    }
    cout << endl;
    params.print();

    if (odds > 100'000'000'000){
        cout << "Warning: The frame you are searching for is extremely rare." << endl;
        cout << "This search may take a long time..." << endl;
        cout << endl;
    }
    if (2 * odds > params.frames()){
        cout << "Warning: There is high chance you will not find a match" << endl;
        cout << "within the current search window." << endl;
        cout << endl;
    }

    cout << "Starting Search..." << endl << endl;
    auto start = std::chrono::system_clock::now();
    {
        DistantSearchSession session(pokemon, filter, params, odds);
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;

    cout << endl;
    cout << "Search Finished: " << diff.count() << " seconds" << endl;
    cout << endl;
}

}
}
