# Pokemon-SwSh-Seed-Generator
Generate perfect den seeds for raid seed injection.

This minimal user-unfriendly project will let you parallel search trillions of frames for the perfect raid seed.

Requirements:
 - Visual Studio 2019

To use:
 1. Modify Main.cpp with the desired stats and filters.
 2. Compile and run. (make sure you turn on optimizations!)

The program will automatically print out any matching seeds that it finds as well as how many skips away from the starting seed.

It takes about 15 min. to search 1 trillion seeds on a slightly overclocked 10-core Skylake processor. This seems to be sufficient to find even the rarest of perfect frames. The example that's currently hard-coded is for a perfect Hatterene which has 12 perfect frames within 1 trillion skips of a real starting seed.

-----

**Credits:**

Much of the code here has been forked from: https://github.com/Admiral-Fish/RaidFinder
