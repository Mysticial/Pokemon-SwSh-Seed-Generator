
#ifdef ENABLE_13_AVX2

#include "Tools/XoroShiro4_AVX2.h"
#include "TestSeed.h"
#include "TestShiny4_AVX2.h"
namespace SeedGenerator{
namespace DistantSearch{

void test_shiny_AVX2(
    SeedReporter& reporter,
    const PokemonSpec& pokemon,
    const SearchFilter& filter,
    uint64_t seed, uint64_t skips,
    uint64_t iterations
){
    __m256i vseed = _mm256_set1_epi64x(seed + skips * 0x82A2B175229D6A5B);
    vseed = _mm256_add_epi64(vseed, _mm256_setr_epi64x(0, 9413281287807789659, 379818501906027702, 9793099789713817361));
    while (iterations >= 4){

        XoroShiroX4 rng(vseed);
        rng.next();

        __m256i sidtid  = rng.get_int32(); rng.next();
        __m256i pid     = rng.get_int32();

        __m256i sv = _mm256_xor_si256(sidtid, pid);
        sv = _mm256_xor_si256(sv, _mm256_srli_epi64(sv, 16));
        sv = _mm256_and_si256(sv, _mm256_set1_epi64x(0x000000000000fff0));

        sv = _mm256_cmpeq_epi64(sv, _mm256_setzero_si256());
        if (!_mm256_testz_si256(sv, sv)){
            //  Shinies found. Re-test each one individually.
            test_seed_Default(reporter, pokemon, filter, seed, skips, 4);
        }

        vseed = _mm256_add_epi64(vseed, _mm256_set1_epi64x(4 * 0x82A2B175229D6A5B));
        skips += 4;
        iterations -= 4;
    }

    test_seed_Default(reporter, pokemon, filter, seed, skips, iterations);
}


}
}
#endif
