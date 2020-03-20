
#include <mutex>
#include <iostream>
#include "Tools/Tools.h"
#include "Tools/XoroShiro.h"
#include "ScanSeed_Default.h"
using std::cout;
using std::endl;

namespace SeedGenerator{
namespace SeedCalculator{

std::mutex print_lock;

bool check_IVs(const IvFilter& filter, uint32_t ec, int shiny, uint64_t seed, XoroShiro rng, int max_IVs){
    char IVs[6] = {-1, -1, -1, -1, -1, -1};
    char characteristic = -1;

    //  Forced max IVs.
    for (u8 i = 0; i < max_IVs;){
        u8 index = static_cast<u8>(rng.nextInt(6, 7));
        if (IVs[index] == -1){
            IVs[index] = 31;
            i++;
        }
    }

    // Fill rest of IVs with rand calls
    for (u8 i = 0; i < 6; i++){
        if (IVs[i] == -1){
            IVs[i] = static_cast<u8>(rng.nextInt(31));
        }
        int filters = filter[i];
        if (filters != -1 && IVs[i] != filters){
            return false;
        }
    }

    characteristic = getCharacteristic(ec, IVs);

    std::lock_guard<std::mutex> lg(print_lock);
    cout << tostr_hex_padded(seed) << " : " << SHINY_TYPE[shiny] << " (" << max_IVs << " max IVs) " << dump_IVs(IVs, characteristic) << endl;

    return true;
}

#if 0
bool test_nonshiny_seed(const CalculateSeedParameters& params, uint64_t seed){
    XoroShiro rng(seed);

    uint32_t ec = rng.nextInt(0xffffffff);
    if (ec != params.ec()){
        return false;
    }

    uint32_t sidtid = rng.nextInt(0xffffffff);
    uint32_t pid = rng.nextInt(0xffffffff);

    if ((pid ^ params.pid()) & 0x7fffffff){
        return false;
    }

    uint16_t ftsv = getSv(sidtid);
    uint16_t psv = getSv(pid);

    if (ftsv == psv){
        return false;
    }

    bool found = false;
    for (int c = 1; c <= 5; c++){
        found |= check_IVs(params.IVs(), ec, seed, rng, c);
    }

    return found;
}
uint64_t test_nonshiny_seed_Default(const CalculateSeedParameters& params, uint64_t seed, uint64_t iterations){
    uint64_t found = 0;
    while (iterations--){
        if (test_nonshiny_seed(params, seed)){
            found++;
        }
        seed += 0x0000000100000000;
    }
    return found;
}

bool test_shiny_seed(const CalculateSeedParameters& params, uint64_t seed){
    XoroShiro rng(seed);

    uint32_t ec = rng.nextInt(0xffffffff);
    if (ec != params.ec()){
        return false;
    }

    uint32_t sidtid = rng.nextInt(0xffffffff);
    uint32_t pid = rng.nextInt(0xffffffff);
    if ((uint16_t)pid != (uint16_t)params.pid()){
        return false;
    }

    uint16_t ftsv = getSv(sidtid);
    uint16_t psv = getSv(pid);

    int shiny = 0;
    if (ftsv == psv){
        shiny = getShinyType(sidtid, pid);
    }
    if (params.shiny() == ShinyType::SQUARE && shiny != 2){
        return false;
    }
    if (params.shiny() != ShinyType::SQUARE && shiny != 1){
        return false;
    }

//    cout << std::hex << seed << endl;

    bool found = false;
    for (int c = 1; c <= 5; c++){
        found |= check_IVs(params.IVs(), ec, seed, rng, c);
    }

    return found;
}
uint64_t test_shiny_seed_Default(const CalculateSeedParameters& params, uint64_t seed, uint64_t iterations){
    uint64_t found = 0;
    while (iterations--){
        if (test_shiny_seed(params, seed)){
            found++;
        }
        seed += 0x0000000100000000;
    }
    return found;
}
#endif


bool test_seed(const CalculateSeedParameters& params, uint64_t seed){
    XoroShiro rng(seed);

    uint32_t ec = rng.nextInt(0xffffffff);
    if (ec != params.ec()){
        return false;
    }

    uint32_t sidtid = rng.nextInt(0xffffffff);
    uint32_t pid = rng.nextInt(0xffffffff);

    //  Bottom 16 bits of PID must match.
    if ((uint16_t)pid != (uint16_t)params.pid()){
        return false;
    }

    //  Calculate shiny type.
    uint16_t ftsv = getSv(sidtid);
    uint16_t psv = getSv(pid);
    int shiny = 0;
    if (ftsv == psv){
        shiny = getShinyType(sidtid, pid);
    }

//    //  Shiny type doesn't match.
//    if ((int)params.shiny() != shiny){
//        return false;
//    }

    //  If not shiny, the bottom 31 bits of PID must match.
    if (shiny == 0 && ((pid ^ params.pid()) & 0x7fffffff)){
        return false;
    }

//    if (shiny != 0){
//    }

    //  Check the IVs.
    bool found = false;
    for (int c = 1; c <= 5; c++){
        found |= check_IVs(params.IVs(), ec, shiny, seed, rng, c);
    }
    return found;
}

uint64_t test_seed_Default(const CalculateSeedParameters& params, uint64_t seed, uint64_t iterations){
    uint64_t found = 0;
    while (iterations--){
        if (test_seed(params, seed)){
            found++;
        }
        seed += 0x0000000100000000;
    }
    return found;
}


}
}

