
#pragma once
#ifndef SeedGenerator_XoroShiro2_SSE2_H
#define SeedGenerator_XoroShiro2_SSE2_H

#include <emmintrin.h>
namespace SeedGenerator{

class XoroShiroX2{
public:
    XoroShiroX2(__m128i seed){
        state[0] = seed;
        state[1] = _mm_set1_epi64x(0x82A2B175229D6A5B);
    }

    __m128i get_int32(){
        __m128i x = _mm_add_epi64(state[0], state[1]);
        x = _mm_and_si128(x, _mm_set1_epi64x(0x00000000ffffffff));
        return x;
    }
    void next(){
        __m128i s0 = state[0];
        __m128i s1 = state[1];
        s1 = _mm_xor_si128(s1, s0);

        s0 = _mm_or_si128(_mm_slli_epi64(s0, 24), _mm_srli_epi64(s0, 40));
        state[1] = _mm_or_si128(_mm_slli_epi64(s1, 37), _mm_srli_epi64(s1, 27));

        s1 = _mm_xor_si128(s1, _mm_slli_epi64(s1, 16));
        state[0] = _mm_xor_si128(s0, s1);
    }

private:
    __m128i state[2];
};


}
#endif
