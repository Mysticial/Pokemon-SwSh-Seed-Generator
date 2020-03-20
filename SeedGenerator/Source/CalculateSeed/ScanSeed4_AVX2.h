
#pragma once
#ifndef SeedGenerator_ScanSeed4_AVX2_H
#define SeedGenerator_ScanSeed4_AVX2_H

#include "CalculateSeedParameters.h"
namespace SeedGenerator{
namespace SeedCalculator{

uint64_t test_seed_AVX2(
    const CalculateSeedParameters& params,
    uint64_t seed,
    uint64_t iterations
);

}
}
#endif
