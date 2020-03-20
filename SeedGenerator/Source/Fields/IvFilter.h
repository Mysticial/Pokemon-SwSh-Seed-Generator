
#pragma once
#ifndef SeedGenerator_IvFilter_H
#define SeedGenerator_IvFilter_H

#include <string>
namespace SeedGenerator{

class IvFilter{
public:
    IvFilter() = default;
    IvFilter(char hp, char atk, char def, char spatk, char spdef, char spd);
    IvFilter(const char*& stream);

    char operator[](size_t iv) const{ return m_ivs[iv]; }
    char characteristic() const{ return m_characteristic_iv; }

    std::string to_string() const;

private:
    void sanitize();

private:
    char m_ivs[6] = {-1, -1, -1, -1, -1, -1};
    char m_characteristic_iv = -1;
};


}
#endif
