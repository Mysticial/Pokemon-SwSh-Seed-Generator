
#ifdef ENABLE_13_AVX2

#include "Tools/XoroShiro4_AVX2.h"
#include "ScanSeed_Default.h"
#include "ScanSeed4_AVX2.h"
namespace SeedGenerator{
namespace SeedCalculator{

uint64_t test_seed_AVX2(
    const CalculateSeedParameters& params,
    uint64_t seed,
    uint64_t iterations
){
    __m256i epid = _mm256_set1_epi64x(params.pid() & 0x0000ffff);

    uint64_t found = 0;
    __m256i vseed = _mm256_set1_epi64x(seed);
    vseed = _mm256_add_epi64(vseed, _mm256_setr_epi64x(
        0, 0x0000000100000000, 0x0000000200000000, 0x0000000300000000
    ));
    while (iterations >= 4){
        XoroShiroX4 rng(vseed);
        rng.next();
        rng.next();

        //  Check that bottom 16 bits of PID matches.
        __m256i pid = rng.get_int32();
        pid = _mm256_and_si256(pid, _mm256_set1_epi64x(0x0000ffff));
        if (_mm256_movemask_epi8(_mm256_cmpeq_epi64(pid, epid))){
            found += test_seed_Default(params, _mm_cvtsi128_si64(_mm256_castsi256_si128(vseed)), 4);
        }

        vseed = _mm256_add_epi64(vseed, _mm256_set1_epi64x(0x0000000400000000));
        iterations -= 4;
    }
    test_seed_Default(params, _mm_cvtsi128_si64(_mm256_castsi256_si128(vseed)), iterations);
    return found;
}

}
}
#endif
