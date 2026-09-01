# Analysis of Algorithms - Assignment 03

Mateo Jimenez

## Structure

- `hanoi/hanoi_recursive.cpp` - recursive Towers of Hanoi, counts total moves
- `hanoi/hanoi_iterative.cpp` - iterative Towers of Hanoi (cyclic pattern, no recursion)
- `hanoi/hanoi_benchmark.cpp` - measures and compares execution time of both versions
  for increasing numbers of disks (empirical analysis)
- `lcg/linear_congruential.cpp` - linear congruential method for generating
  pseudo-random numbers
- `lcg/lcg_benchmark.cpp` - measures execution time for generating increasing
  amounts of pseudo-random numbers (empirical analysis)

## Notes

- Both Hanoi implementations were verified to produce exactly 2^n - 1 moves
  for n = 1 to 30, confirming they are equivalent.
- The full analysis (mathematical + empirical, with the actual measured results)
  is in the submitted PDF, not repeated here.

To compile any file:
```
g++ -O2 -o program file.cpp
./program
```
