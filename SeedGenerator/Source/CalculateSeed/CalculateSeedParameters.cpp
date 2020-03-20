
#include <map>
#include <istream>
#include <sstream>
#include <iostream>
#include "Tools/Tools.h"
#include "CalculateSeedParameters.h"
using std::cout;
using std::endl;

namespace SeedGenerator{
namespace SeedCalculator{


const std::map<std::string, void(*)(const char*&, CalculateSeedParameters&)> CALC_SEED_KEYS{
//    {"Shininess:",  CalculateSeedParameters::parse_shiny},
    {"EC:",         CalculateSeedParameters::parse_ec},
    {"PID:",        CalculateSeedParameters::parse_pid},
    {"IVs:",        CalculateSeedParameters::parse_IVs},
};
//void CalculateSeedParameters::parse_shiny(const char*& stream, CalculateSeedParameters& self){
//    skip_whitespace(stream);
//    std::string token = parse_token(stream);
//    if (token == "NotShiny"){
//        self.m_shiny = ShinyType::NONE;
//        return;
//    }
//    if (token == "Star"){
//        self.m_shiny = ShinyType::STAR;
//        return;
//    }
//    if (token == "Square"){
//        self.m_shiny = ShinyType::SQUARE;
//        return;
//    }
//    throw "Invalid Shiny Type: " + token;
//}
void CalculateSeedParameters::parse_ec(const char*& stream, CalculateSeedParameters& self){
    skip_whitespace(stream);
    std::string token = parse_token(stream);
    const char* str = token.c_str();
    self.m_ec = (uint32_t)parse_hex(str);
}
void CalculateSeedParameters::parse_pid(const char*& stream, CalculateSeedParameters& self){
    skip_whitespace(stream);
    std::string token = parse_token(stream);
    const char* str = token.c_str();
    self.m_pid = (uint32_t)parse_hex(str);
}
void CalculateSeedParameters::parse_IVs(const char*& stream, CalculateSeedParameters& self){
    self.m_IVs = IvFilter(stream);
}

CalculateSeedParameters::CalculateSeedParameters(std::istream& stream){
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

        auto iter = CALC_SEED_KEYS.find(token);
        if (iter == CALC_SEED_KEYS.end()){
            throw "Unrecognized Token: " + token;
        }

        if (iter->second == nullptr){
            continue;
        }
        iter->second(str, *this);
    }
}

void CalculateSeedParameters::print(){
//    std::string pid = m_shiny == ShinyType::NONE
//        ? tostr_hex_padded(m_pid, 8)
//        : "xxxx" + tostr_hex_padded(m_pid & 0x0000ffff, 4);

    cout << "Calculate Seed for Den Pokemon:" << endl;
//    cout << "    Shiny Type:     " << SHINY_TYPE[(int)m_shiny] << endl;
    cout << "    EC:             " << tostr_hex_padded(m_ec, 8) << endl;
    cout << "    PID:            " << tostr_hex_padded(m_pid, 8) << endl;
    cout << "    IVs:            " << m_IVs.to_string() << endl;
    cout << endl;
}


}
}
