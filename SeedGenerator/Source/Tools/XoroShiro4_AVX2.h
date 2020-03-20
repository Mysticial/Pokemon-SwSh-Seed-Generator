
#pragma once
#ifndef SeedGenerator_XoroShiro4_AVX2_H
#define SeedGenerator_XoroShiro4_AVX2_H

#include <immintrin.h>
namespace SeedGenerator{

class XoroShiroX4{
public:
    XoroShiroX4(__m256i seed){
        state[0] = seed;
        state[1] = _mm256_set1_epi64x(0x82A2B175229D6A5B);
    }

    __m256i get_int32(){
        __m256i x = _mm256_add_epi64(state[0], state[1]);
        x = _mm256_and_si256(x, _mm256_set1_epi64x(0x00000000ffffffff));
        return x;
    }
    void next(){
        __m256i s0 = state[0];
        __m256i s1 = state[1];
        s1 = _mm256_xor_si256(s1, s0);

        s0 = _mm256_or_si256(_mm256_slli_epi64(s0, 24), _mm256_srli_epi64(s0, 40));
        state[1] = _mm256_or_si256(_mm256_slli_epi64(s1, 37), _mm256_srli_epi64(s1, 27));

        s1 = _mm256_xor_si256(s1, _mm256_slli_epi64(s1, 16));
        state[0] = _mm256_xor_si256(s0, s1);
    }

private:
    __m256i state[2];
};

}
#endif
