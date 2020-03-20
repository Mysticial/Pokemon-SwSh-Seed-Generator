
#pragma once
#ifndef SeedGenerator_Tools_H
#define SeedGenerator_Tools_H

#include <string>
namespace SeedGenerator{

std::string tostr_commas(uint64_t x);
std::string tostr_hex_padded(uint64_t x, size_t length = 16);

void skip_whitespace(const char*& stream);
uint64_t parse_dec(const char*& stream);
uint64_t parse_hex(const char*& stream);
std::string parse_token(const char*& stream);

std::string dump_IVs(const char IVs[6], char characteristic);

}
#endif
