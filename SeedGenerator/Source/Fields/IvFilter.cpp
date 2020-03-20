
#include "Tools/Tools.h"
#include "IvFilter.h"
#include <iostream>
using namespace std;

namespace SeedGenerator{

IvFilter::IvFilter(char hp, char atk, char def, char spatk, char spdef, char spd){
    m_ivs[0] = hp;
    m_ivs[1] = atk;
    m_ivs[2] = def;
    m_ivs[3] = spatk;
    m_ivs[4] = spdef;
    m_ivs[5] = spd;
    sanitize();
}

IvFilter::IvFilter(const char*& stream){
    for (int c = 0; c < 6; c++){
        skip_whitespace(stream);
        std::string token = parse_token(stream);
        if (token == "x"){
            m_ivs[c] = -1;
            continue;
        }
        if (token == "31*"){
            m_ivs[c] = 32;
            continue;
        }
        const char* str = token.c_str();
        uint64_t val = parse_dec(str);
        if (val > 31 || str != &token.back() + 1){
            throw "Invalid IV: " + token;
        }
        m_ivs[c] = (char)val;
    }
    sanitize();
}

void IvFilter::sanitize(){
    m_characteristic_iv = -1;
    for (int c = 0; c < 6; c++){
        char iv = m_ivs[c];
        if (iv < 32){
            continue;
        }
        if (m_characteristic_iv != -1){
            throw "Multiple characteristic IVs specified.";
        }
        m_characteristic_iv = c;
        m_ivs[c] = 31;
    }
}

std::string IvFilter::to_string() const{
    std::string ret;
    for (size_t c = 0; c < 6; c++){
        if (c != 0){
            ret += " ";
        }
        if (m_ivs[c] < 0){
            ret += "x";
        }else{
            ret += std::to_string((int)m_ivs[c]);
        }
        if (c == m_characteristic_iv){
            ret += "*";
        }
    }
    return ret;
}


}
