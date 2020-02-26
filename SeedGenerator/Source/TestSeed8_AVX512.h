
#pragma once
#ifndef SeedGenerator_TestSeed8_H
#define SeedGenerator_TestSeed8_H

#include <immintrin.h>
#include "TestSeed1.h"

class XoroShiroX8{
public:
    XoroShiroX8(__m512i seed){
        state[0] = seed;
        state[1] = _mm512_set1_epi64(0x82A2B175229D6A5B);
    }

    __m512i get_int32(){
        __m512i x = _mm512_add_epi64(state[0], state[1]);
        x = _mm512_and_si512(x, _mm512_set1_epi64(0x00000000ffffffff));
        return x;
    }
    void next(){
        __m512i s0 = state[0];
        __m512i s1 = state[1];
        s1 = _mm512_xor_si512(s1, s0);

        s0 = _mm512_rol_epi64(s0, 24);
        state[1] = _mm512_rol_epi64(s1, 37);

        s1 = _mm512_xor_si512(s1, _mm512_slli_epi64(s1, 16));
        state[0] = _mm512_xor_si512(s0, s1);
    }

private:
    __m512i state[2];
};

void test_seed8(const Pokemon& pokemon, const Filter& filter, u64 seed, u64 skips){
    __m512i vseed = _mm512_set1_epi64(seed + skips * 0x82A2B175229D6A5B);
    vseed = _mm512_add_epi64(vseed, _mm512_setr_epi64(
        0, 9413281287807789659, 379818501906027702, 9793099789713817361,
        759637003812055404, 10172918291619845063, 1139455505718083106, 10552736793525872765
    ));

    XoroShiroX8 rng(vseed);
    rng.next();

    __m512i sidtid  = rng.get_int32(); rng.next();
    __m512i pid     = rng.get_int32();

    __m512i sv = _mm512_xor_si512(sidtid, pid);
    sv = _mm512_xor_si512(sv, _mm512_srli_epi64(sv, 16));

    sv = _mm512_and_si512(sv, _mm512_set1_epi64(0x000000000000fff0));

    if (!_mm512_cmpeq_epi64_mask(sv, _mm512_setzero_si512())){
        //  No shinies found. Exit early.
        return;
    }

    //  Shinies found. Re-test each one individually.
    test_seed(pokemon, filter, seed, skips + 0);
    test_seed(pokemon, filter, seed, skips + 1);
    test_seed(pokemon, filter, seed, skips + 2);
    test_seed(pokemon, filter, seed, skips + 3);
    test_seed(pokemon, filter, seed, skips + 4);
    test_seed(pokemon, filter, seed, skips + 5);
    test_seed(pokemon, filter, seed, skips + 6);
    test_seed(pokemon, filter, seed, skips + 7);
}






#endif
