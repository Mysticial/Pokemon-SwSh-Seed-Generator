
#ifdef ENABLE_17_AVX512

#include "Tools/XoroShiro8_AVX512.h"
#include "ScanSeed_Default.h"
#include "ScanSeed8_AVX512.h"
namespace SeedGenerator{
namespace SeedCalculator{
    
uint64_t test_seed_AVX512(
    const CalculateSeedParameters& params,
    uint64_t seed,
    uint64_t iterations
){
    __m512i epid = _mm512_set1_epi64(params.pid() & 0x0000ffff);

    uint64_t found = 0;
    __m512i vseed = _mm512_set1_epi64(seed);
    vseed = _mm512_add_epi64(vseed, _mm512_setr_epi64(
                         0, 0x0000000100000000, 0x0000000200000000, 0x0000000300000000,
        0x0000000400000000, 0x0000000500000000, 0x0000000600000000, 0x0000000700000000
    ));
    while (iterations >= 8){
        XoroShiroX8 rng(vseed);
        rng.next();
        rng.next();

        //  Check that bottom 16 bits of PID matches.
        __m512i pid = rng.get_int32();
        pid = _mm512_and_si512(pid, _mm512_set1_epi64(0x0000ffff));
        if (_mm512_cmpeq_epi64_mask(pid, epid)){
            found += test_seed_Default(params, _mm_cvtsi128_si64(_mm512_castsi512_si128(vseed)), 8);
        }

        vseed = _mm512_add_epi64(vseed, _mm512_set1_epi64(0x0000000800000000));
        iterations -= 8;
    }
    test_seed_Default(params, _mm_cvtsi128_si64(_mm512_castsi512_si128(vseed)), iterations);
    return found;
}


}
}
#endif
