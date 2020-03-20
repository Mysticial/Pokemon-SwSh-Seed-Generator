
#ifdef ENABLE_07_SSE41

#include <smmintrin.h>
#include "Tools/XoroShiro2_SSE2.h"
#include "TestSeed.h"
#include "TestShiny2_SSE41.h"
namespace SeedGenerator{
namespace DistantSearch{

void test_shiny_SSE41(
    SeedReporter& reporter,
    const PokemonSpec& pokemon,
    const SearchFilter& filter,
    uint64_t seed, uint64_t skips,
    uint64_t iterations
){
    __m128i vseed = _mm_set1_epi64x(seed + skips * 0x82A2B175229D6A5B);
    vseed = _mm_add_epi64(vseed, _mm_setr_epi32(0, 0, 0x229D6A5B, 0x82A2B175));
    while (iterations >= 2){
        XoroShiroX2 rng(vseed);
        rng.next();

        __m128i sidtid  = rng.get_int32(); rng.next();
        __m128i pid     = rng.get_int32();

        __m128i sv = _mm_xor_si128(sidtid, pid);
        sv = _mm_xor_si128(sv, _mm_srli_epi64(sv, 16));
        sv = _mm_and_si128(sv, _mm_set1_epi64x(0x000000000000fff0));

        sv = _mm_cmpeq_epi64(sv, _mm_setzero_si128());
        if (!_mm_testz_si128(sv, sv)){
            //  Shinies found. Re-test each one individually.
            test_seed_Default(reporter, pokemon, filter, seed, skips, 2);
        }

        vseed = _mm_add_epi64(vseed, _mm_set1_epi64x(2 * 0x82A2B175229D6A5B));
        skips += 2;
        iterations -= 2;
    }

    test_seed_Default(reporter, pokemon, filter, seed, skips, iterations);
}


}
}
#endif
