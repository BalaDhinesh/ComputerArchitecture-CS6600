# ComputerArchitecture CS6600 course Assignment
This repository provides the assignments done as part of Computer Architecture Graduate Level course (CS6600) at IIT Madras.
This project is done in collaboration with [Vishnu Varma](https://github.com/Vishnu2912).

## Assignment - 1: Cachegrind
In this assignment we utilize Cachegrind simulator to collect various cache statistics such as instruction references, L1 I-Cache misses, L1 D-Cache misses, L2 cache misses etc... for different cache configurations such as associativity, block size, cache sizes etc...

Source code is available here [A1-Cachegrind](./A1-Cachegrind/)
## Assignment - 2: Design own LLC replacement policy
This assignment aims to implement your own LLC replacement policy using the Champsim simulator and benchmark it against the replacement policies such as [SHiP](https://mrmgroup.cs.princeton.edu/papers/MICRO11_SHiP_Wu_Final.pdf), [Hawkeye](https://www.cs.utexas.edu/~lin/papers/isca16.pdf) and [Mockingjay](https://www.cs.utexas.edu/~lin/papers/hpca22.pdf).

Source code is available here [A2-cache-replacement-policy](./A2-cache-replacement-policy/)

## Assignment - 3: Design own Branch predictor
In this assignment we are required to implement our own branch predictor using the ChampSim simulator. ChampSim has 4 branch predictors implemented in the branch/ folder from ChampSim: bimodal, gshare, perceptron and hashed perceptron.

Source code is available here [A3-Branch-prediction](./A3-Branch-prediction/)

## Assignment - 4: Design own Data Prefetcher
In this assignment we are required to implement our own data prefetching policy for the using the ChampSim simulator.

Source code is available here [A4-Data-prefetcher](./A4-Data-prefetcher/)

## References:
Cachegrind simulator: https://valgrind.org/docs/manual/cg-manual.html

ChampSim simulator: https://github.com/ChampSim/ChampSim
