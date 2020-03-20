# SeedGen

SeedGen has two features:
 1. Calculate Seed
 2. Distant Search

**Calculate Seed:**

Given the PID, EC, and IVs for den Pokemon, calculate the seed(s) that could produce it. This is no different from all other seed calculates like those built into Dudu. The only difference is that this will work for shinies as well.

If no seed is found, it means that either the input is incorrect, or the Pokemon is illegal (and likely hacked). A lot of improperly genned den Pokemon will not have a seed associated with it. These are all illegal.

```
Calculate Seed for Den Pokemon:
    EC:             a82735a3
    PID:            d606b081
    IVs:            31 23 31 31* 6 1

Searching...

029384ca8589cb48 : Star   (3 max IVs) {31, 23, 31, 31*, 6, 1}

Search Finished: 0.187505 seconds

Seed(s) found. For legality checking, please verify remaining stats with RaidFinder.

Press any key to continue . . .
```

**Distant Search:**

This is the main feature of SeedGen. Given a starting seed, search billions/trillions of skips into the future for a frame that has everything you want. The purpose of this feature is seed injection via CFW.

Want a square shiny Gmax Hatterene that is 0atk+0spd Quiet and Mischievous characteristic for maximum Yandere? No problem.

```
Pokemon Spec:
    Max IVs:    4
    Ability:    hidden possible
    Gender:     100% female

Desired Stats:
    Shiny:      Square
    IVs:        {31, 0, 31, 31*, 31, 0}
    Ability:    Hidden
    Nature:     Quiet
    Gender:     Female

Odds:
    Shininess:     1 in 65,536
    IV Spread:     1 in 61,440  (including characteristic)
    Nature:        1 in 25
    Gender:        1 in 1
    Ability:       1 in 3
    Total Odds:    1 in 301,989,888,000

Search Parameters:
    Starting Seed:  4399e7e35f921e09
    Max Results:    10
    Max Frames:     1,000,000,000,000
    Arch:           AVX512
    Threads:        20

Warning: The frame you are searching for is extremely rare.
This search may take a long time...

Starting Search...

21154d7237cef633 : Skips = 87,312,686,238 - Square {31, 0, 31, 31*, 31, 0} Quiet, Ability H, Gender #-1 (female)
afbf7965dcde6ea5 : Skips = 157,698,538,644 - Square {31, 0, 31, 31*, 31, 0} Quiet, Ability H, Gender #-1 (female)
ce08154acd1db7e0 : Skips = 361,816,379,189 - Square {31, 0, 31, 31*, 31, 0} Quiet, Ability H, Gender #-1 (female)
fa566e7cea780246 : Skips = 480,751,337,287 - Square {31, 0, 31, 31*, 31, 0} Quiet, Ability H, Gender #-1 (female)
40cde6fbfcc9da8f : Skips = 500,295,082,098 - Square {31, 0, 31, 31*, 31, 0} Quiet, Ability H, Gender #-1 (female)
301d2e750dea3eda : Skips = 518,764,351,811 - Square {31, 0, 31, 31*, 31, 0} Quiet, Ability H, Gender #-1 (female)
ac5bd963780ee05f : Skips = 755,636,959,970 - Square {31, 0, 31, 31*, 31, 0} Quiet, Ability H, Gender #-1 (female)
2c6a4cab5c3404e3 : Skips = 801,763,977,134 - Square {31, 0, 31, 31*, 31, 0} Quiet, Ability H, Gender #-1 (female)
9a924f23e200b7c2 : Skips = 946,487,525,499 - Square {31, 0, 31, 31*, 31, 0} Quiet, Ability H, Gender #-1 (female)
17a2cfceeafff02a : Skips = 962,912,749,107 - Square {31, 0, 31, 31*, 31, 0} Quiet, Ability H, Gender #-1 (female)

Search Finished: 43.7431 seconds

Press any key to continue . . .
```

Even though this frame is 1 in 300 billion, SeedGen will usually find a seed for it within minutes depending on how lucky your starting seed is and how powerful your computer is. This search is parallelized and will use all the cores in your system (up to 64 on Windows).

With a modern computer, you can feasibly cherry pick every single visible stat for any possible den Pokemon that has 4 or 5 guaranteed max IVs. With a more powerful computer, you can probably find perfect seeds for 1-3 max IVs Pokemon as well.

In all cases, Distant Search will calculate the rarity of the frame that you are searching for. So you can use this to set your expectations straight on what's possible, what isn't, and how long it may take to find such a seed.

Always double-check the seeds with Raid Finder! SeedGen is loosely thrown together for a specific purpose and it doesn't cover all corner cases.

-----

**How to Use**

SeedGen currently has no UI. Instead, it reads input files.

1. Build the appropriate binary. (see next section)
2. Place the files `CalculateSeed.txt` and `DistantSearch.txt` in the same folder as the binary.
3. Run the binary and select an option.

The binary will automatically read the respective input file for data inputs. Modify these input files to set your own search parameters.


**How to Build**

Requirements:
 - Visual Studio 2019

1. Open the project in Visual Studio 2019.
2. Select a build option. (see below)
3. Click Build.

Build Options:
 - `x86 Release`
 - `x64 Release`
 - `x64 SSE4.1`
 - `x64 AVX2`
 - `x64 AVX512`

Because Distant Search is performance critical, multiple modes with different levels of ISA optimizations are provided.
 - `x64 AVX512`: For Skylake Server and Cannonlake or later.
 - `x64 AVX2`: For Haswell or AMD Zen or later.
 - `x64 SSE4.1`: For Nehalem and AMD Bulldozer or later.

The last two are mostly fallbacks. They aren't at all efficient.

Searching 1 trillion frames on slightly overclocked 10-core Skylake processor takes:
 - `x64 Release`: 10 minutes
 - `x64 AVX2`: 90 seconds
 - `x64 AVX512`: 60 seconds

-----

**Credits:**

Much of the code here has been forked from: https://github.com/Admiral-Fish/RaidFinder
