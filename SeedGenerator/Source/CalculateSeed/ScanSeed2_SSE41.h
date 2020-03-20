
#pragma once
#ifndef SeedGenerator_ScanSeed2_SSE41_H
#define SeedGenerator_ScanSeed2_SSE41_H

#include "CalculateSeedParameters.h"
namespace SeedGenerator{
namespace SeedCalculator{

uint64_t test_seed_SSE41(
    const CalculateSeedParameters& params,
    uint64_t seed,
    uint64_t iterations
);

}
}
#endif
