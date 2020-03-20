
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include "Tools/Tools.h"
#include "Tools/XoroShiro.h"
//#include "DistantSearch/ParallelSearch.h"
#include "PokemonSpec.h"
#include "CalculateSeed/CalculateSeed.h"
#include "DistantSearch/SearchFilter.h"
#include "DistantSearch/TestSeed.h"
#include "DistantSearch/DistantSearch.h"
using std::cout;
using std::endl;


using namespace SeedGenerator::SeedCalculator;
using namespace SeedGenerator::DistantSearch;



int main(){

    try{
        cout << "SeedGenerator 1.1 - by Mysticial" << endl;
        cout << endl;

        cout << "Choose an Option:" << endl;
        cout << "    0    Calculate Seed: Calculate Seed for a given den Pokemon." << endl;
        cout << "    1    Distant Search: Search billions of frames for a perfect den seed." << endl;
        cout << endl;

        int choice = -1;

        while (choice < 0 || choice > 1){
            cout << "option: ";
            std::cin >> choice;
        }

        cout << endl << endl;

        switch (choice){
        case 0:{
            const char* filename = "CalculateSeed.txt";
            cout << "Loading File: " << filename << endl << endl;
            std::ifstream file(filename);
            calculate_seed(file);
            break;
        }case 1:{
            const char* filename = "DistantSearch.txt";
            cout << "Loading File: " << filename << endl << endl;
            std::ifstream file(filename);
            distant_search(file);
            break;
        }}

    }catch (std::string& err){
        cout << err << endl << endl;
    }catch (const char* err){
        cout << err << endl << endl;
    }


#ifdef _WIN32
    system("pause");
#endif
}


