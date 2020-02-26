# Pokemon-SwSh-Seed-Generator
Generate perfect den seeds for raid seed injection.

This minimal user-unfriendly project will let you parallel search trillions of frames for the perfect raid seed.

Requirements:
 - Visual Studio 2019

To use:
 1. Modify `Main.cpp` with the desired stats and filters.
 2. Change the build option to `Release` (and optionally x64).
 3. Compile and run.

The program will automatically print out any matching seeds that it finds as well as how many skips away from the starting seed. The search is not done in any particular order due to the parallelization.

Always double-check the seeds with Raid Finder! This program is loosely thrown together for a specific purpose and it doesn't cover all corner cases.

Build Options:
 - `x86 Release`
 - `x64 Release`
 - `x64 AVX2`
 - `x64 AVX512`

If your processor supports AVX2 and/or AVX512, you should choose those instead. The program is much faster with either AVX2 or AVX512.

On a slightly overclocked 10-core Skylake processor:
 - `x64 Release`: 15 minutes
 - `x64 AVX2`: 90 seconds
 - `x64 AVX512`: 60 seconds

This seems to be sufficient to find even the rarest of perfect frames. The example that's currently hard-coded is for a perfect Hatterene which has 12 perfect frames within 1 trillion skips of a real starting seed.

-----

**Credits:**

Much of the code here has been forked from: https://github.com/Admiral-Fish/RaidFinder
