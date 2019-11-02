# Pengine

[![CircleCI](https://circleci.com/gh/LoicNassif/lightweight-physics-engine/tree/feature%2Fgcc_compatibility.svg?style=svg)](https://circleci.com/gh/LoicNassif/lightweight-physics-engine/tree/feature%2Fgcc_compatibility)

Currently tested on the following platforms,
- `MSVC` using `MSBuild version 16.2.37902` on `Windows 8.1`.
- `gcc` using version `7.4.0` on `Ubuntu 18.04.1 LTS`.
- `clang` using version `8.0.0-3` on `Ubuntu 18.04.1 LTS`. 

## Building

Create and enter a `build` folder inside your project folder. Specify your generator and compiler for cmake, for example,
```bash
cmake -G "Unix Makefiles" -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++ ../
```
