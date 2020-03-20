
#ifdef ENABLE_07_SSE41

#include <smmintrin.h>
#include "Tools/XoroShiro2_SSE2.h"
#include "ScanSeed_Default.h"
#include "ScanSeed2_SSE41.h"
namespace SeedGenerator{
namespace SeedCalculator{

uint64_t test_seed_SSE41(
    const CalculateSeedParameters& params,
    uint64_t seed,
    uint64_t iterations
){
    __m128i epid = _mm_set1_epi64x(params.pid() & 0x0000ffff);

    uint64_t found = 0;
    __m128i vseed = _mm_set1_epi64x(seed);
    vseed = _mm_add_epi64(vseed, _mm_setr_epi32(0, 0, 0, 1));
    while (iterations >= 2){
        XoroShiroX2 rng(vseed);
        rng.next();
        rng.next();

        //  Check that bottom 16 bits of PID matches.
        __m128i pid = rng.get_int32();
        pid = _mm_and_si128(pid, _mm_set1_epi64x(0x0000ffff));
        if (_mm_movemask_epi8(_mm_cmpeq_epi64(pid, epid))){
            found += test_seed_Default(params, _mm_cvtsi128_si64(vseed), 2);
        }

        vseed = _mm_add_epi64(vseed, _mm_set1_epi64x(0x0000000200000000));
        iterations -= 2;
    }
    test_seed_Default(params, _mm_cvtsi128_si64(vseed), iterations);
    return found;
}

}
}
#endif
