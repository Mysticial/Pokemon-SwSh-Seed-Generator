
#include <sstream>
#include "Tools.h"
namespace SeedGenerator{

std::string tostr_commas(uint64_t x){
    //  Prints out x with comma separators.

    std::string str = std::to_string(x);
    std::string out;

    const char* ptr = str.c_str();
    size_t len = str.size();

    size_t commas = (len + 2) / 3 - 1;
    size_t shift = len - commas * 3;

    while (1){
        char ch = *ptr++;
        if (ch == '\0')
            break;
        if (shift == 0){
            out += ',';
            shift = 3;
        }
        out += ch;
        shift--;
    }

    return out;
}
std::string tostr_hex_padded(uint64_t x, size_t length){
    std::stringstream ss;
    ss << std::hex << x << std::dec;
    std::string str = ss.str();
    if (str.size() < length){
        str = std::string(length - str.size(), '0') + str;
    }
    return str;
}

void skip_whitespace(const char*& stream){
    while (true){
        char ch = stream[0];
        if (ch != ' ' && ch != '\t'){
            break;
        }
        stream++;
    }
}
uint64_t parse_dec(const char*& stream){
    uint64_t x = 0;
    while (true){
        char ch = stream[0];
        if (ch == ','){
            stream++;
            continue;
        }
        if (ch < '0' || ch > '9'){
            break;
        }
        x *= 10;
        x += ch - '0';
        stream++;
    }
    return x;
}
uint64_t parse_hex(const char*& stream){
    if (stream[0] == '0' && stream[1] == 'x'){
        stream += 2;
    }

    uint64_t x = 0;
    while (true){
        char ch = stream[0];
        char digit;
        if ('0' <= ch && ch <= '9'){
            digit = ch - '0';
        }else if ('a' <= ch && ch <= 'f'){
            digit = ch - 'a' + 10;
        }else if ('A' <= ch && ch <= 'F'){
            digit = ch - 'A' + 10;
        }else{
            break;
        }
        x *= 16;
        x += digit;
        stream++;
    }
    return x;
}
std::string parse_token(const char*& stream){
    std::string str;
    while (true){
        char ch = stream[0];
        if (ch <= 32){
            break;
        }
        if (ch == '/' && stream[1] == '/'){
            break;
        }
        str += ch;
        stream++;
    }
    return str;
}



std::string dump_IVs(const char IVs[6], char characteristic){
    std::stringstream ss;
    ss << "{"  << (int)IVs[0] << (characteristic == 0 ? "*" : "")
       << ", " << (int)IVs[1] << (characteristic == 1 ? "*" : "")
       << ", " << (int)IVs[2] << (characteristic == 2 ? "*" : "")
       << ", " << (int)IVs[3] << (characteristic == 3 ? "*" : "")
       << ", " << (int)IVs[4] << (characteristic == 4 ? "*" : "")
       << ", " << (int)IVs[5] << (characteristic == 5 ? "*" : "")
       << "}";
    return ss.str();
}

}
