
#pragma once
#ifndef SeedGenerator_ScanSeed8_AVX512_H
#define SeedGenerator_ScanSeed8_AVX512_H

#include "CalculateSeedParameters.h"
namespace SeedGenerator{
namespace SeedCalculator{

uint64_t test_seed_AVX512(
    const CalculateSeedParameters& params,
    uint64_t seed,
    uint64_t iterations
);

}
}
#endif
