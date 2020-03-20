/*
 * This file is part of RaidFinder
 * Copyright (C) 2019-2020 by Admiral_Fish
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef XOROSHIRO_HPP
#define XOROSHIRO_HPP

#include "Global.h"
namespace SeedGenerator{

class XoroShiro
{
public:
    XoroShiro();
    explicit XoroShiro(u64 seed);
    void setSeed(u64 seed);
    u32 nextInt(u32 max, u32 mask, int &count);
    u32 nextInt(u32 max, u32 mask);
    u32 nextInt(u32 mask);

private:
    u64 state[2];

    u64 next();
};


static inline u16 getSv(u32 val){
    return ((val >> 16) ^ (val & 0xFFFF)) >> 4;
}
static inline u8 getShinyType(u32 sidtid, u32 pid){
    u16 val = (sidtid ^ pid) >> 16;
    if ((val ^ (sidtid & 0xffff)) == (pid & 0xffff))
    {
        return 2; // Square shiny
    }

    return 1; // Star shiny
}
static inline char getCharacteristic(u32 ec, const char ivs[6]){
    const u8 statOrder[6] = { 0, 1, 2, 5, 3, 4 };

    u8 charStat = ec % 6;
    for (u8 i = 0; i < 6; i++)
    {
        u8 stat = statOrder[(charStat + i) % 6];
        if (ivs[stat] == 31)
        {
            return stat;
        }
    }
    return statOrder[charStat];
}



}
#endif // XOROSHIRO_HPP
