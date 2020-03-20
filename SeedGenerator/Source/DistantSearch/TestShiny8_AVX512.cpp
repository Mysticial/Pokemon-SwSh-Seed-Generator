
#ifdef ENABLE_17_AVX512

#include "Tools/XoroShiro8_AVX512.h"
#include "TestSeed.h"
#include "TestShiny8_AVX512.h"
namespace SeedGenerator{
namespace DistantSearch{

void test_shiny_AVX512(
    SeedReporter& reporter,
    const PokemonSpec& pokemon,
    const SearchFilter& filter,
    uint64_t seed, uint64_t skips,
    uint64_t iterations
){
    size_t found = 0;
    __m512i vseed = _mm512_set1_epi64(seed + skips * 0x82A2B175229D6A5B);
    vseed = _mm512_add_epi64(vseed, _mm512_setr_epi64(
        0, 9413281287807789659, 379818501906027702, 9793099789713817361,
        759637003812055404, 10172918291619845063, 1139455505718083106, 10552736793525872765
    ));
    while (iterations >= 8){
        XoroShiroX8 rng(vseed);
        rng.next();

        __m512i sidtid  = rng.get_int32(); rng.next();
        __m512i pid     = rng.get_int32();

        __m512i sv = _mm512_xor_si512(sidtid, pid);
        sv = _mm512_xor_si512(sv, _mm512_srli_epi64(sv, 16));
        sv = _mm512_and_si512(sv, _mm512_set1_epi64(0x000000000000fff0));

        if (_mm512_cmpeq_epi64_mask(sv, _mm512_setzero_si512())){
            //  Shinies found. Re-test each one individually.
            test_seed_Default(reporter, pokemon, filter, seed, skips, 8);
        }

        vseed = _mm512_add_epi64(vseed, _mm512_set1_epi64(8 * 0x82A2B175229D6A5B));
        skips += 8;
        iterations -= 8;
    }

    test_seed_Default(reporter, pokemon, filter, seed, skips, iterations);
}

}
}
#endif
