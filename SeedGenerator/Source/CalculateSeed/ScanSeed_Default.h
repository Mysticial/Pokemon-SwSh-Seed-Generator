
#pragma once
#ifndef SeedGenerator_ScanSeed_Default_H
#define SeedGenerator_ScanSeed_Default_H

#include "CalculateSeedParameters.h"
namespace SeedGenerator{
namespace SeedCalculator{

uint64_t test_seed_Default(const CalculateSeedParameters& params, uint64_t seed, uint64_t iterations);

}
}
#endif
