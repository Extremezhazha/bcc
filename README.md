# BCC
Welcome to Bad Calculator Compiler, where we waste millions of CPU cycle on computation that should only take a couple. 

## How to use

While I'd like to think this program been made as useless as possible, whenever an ineger calculator is being made, is has some use somewhere. 
By the end of the day, we may all have a moment where we need to calculate addition of two digit numbers, and are too lazy to not use a calculator. 
However, given the intention of making this program somewhat useless and silly, proceed to use the program with caution. 

### What BCC does

Funny name, eh? Does BCC compile calculators, or is it a calculator that is simultaneously a compiler?

Well, as a matter of fact, it's more of a calculator that uses compilers to do evaluation. 

### Dependencies and building
BCC is only tested on Linux (debian testing) so far, requirements include:
```
G++
CMake
Flex
Bison
```

Just use CMake to build the executable and run it in the build directory. The `ext_include` files that are copied into the build directory is necessary too. 
