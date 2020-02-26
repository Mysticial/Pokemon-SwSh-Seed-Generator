
#pragma once
#ifndef SeedGenerator_TestSeed4_H
#define SeedGenerator_TestSeed4_H

#include <immintrin.h>
#include "TestSeed1.h"

//inline static void print_u64(__m256i x){
//    for (int i = 0; i < 4; i++){
//        std::cout << x.m256i_u64[i] << " ";
//    }
//    std::cout << std::endl;
//}

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

void test_seed4(const Pokemon& pokemon, const Filter& filter, u64 seed, u64 skips){
    __m256i vseed = _mm256_set1_epi64x(seed + skips * 0x82A2B175229D6A5B);
    vseed = _mm256_add_epi64(vseed, _mm256_setr_epi64x(0, 9413281287807789659, 379818501906027702, 9793099789713817361));

    XoroShiroX4 rng(vseed);
    rng.next();

    __m256i sidtid  = rng.get_int32(); rng.next();
    __m256i pid     = rng.get_int32();

    __m256i sv = _mm256_xor_si256(sidtid, pid);
    sv = _mm256_xor_si256(sv, _mm256_srli_epi64(sv, 16));

    sv = _mm256_and_si256(sv, _mm256_set1_epi64x(0x000000000000fff0));
    sv = _mm256_cmpeq_epi64(sv, _mm256_setzero_si256());

    if (_mm256_testz_si256(sv, sv)){
        //  No shinies found. Exit early.
        return;
    }

    //  Shinies found. Re-test each one individually.
    test_seed(pokemon, filter, seed, skips + 0);
    test_seed(pokemon, filter, seed, skips + 1);
    test_seed(pokemon, filter, seed, skips + 2);
    test_seed(pokemon, filter, seed, skips + 3);
}

#endif
