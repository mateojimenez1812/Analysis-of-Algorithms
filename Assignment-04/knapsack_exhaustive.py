"""
Lab 04 - Exercise 1
0/1 Knapsack Problem solved via Exhaustive Search (brute force over all subsets).

For a problem of size n, there are 2^n possible subsets of items.
We generate the subsets using itertools.product (bitmasks 0/1 of length n),
check which ones respect the capacity, and keep the best total value.

The script increases n = 3, 4, 5, ... and times the exhaustive search for each
size until a single run takes longer than 30 seconds, then reports the table
of (n, time in seconds) and the largest n solved within the 30s limit.
"""

import random
import time
import itertools


def generate_instance(n, seed=None):
    """Randomly generate weights, values and capacity for a knapsack instance of size n."""
    rng = random.Random(seed)
    weights = [rng.randint(1, 50) for _ in range(n)]
    values = [rng.randint(1, 100) for _ in range(n)]
    capacity = int(0.5 * sum(weights))  # capacity ~ half of total weight, a common convention
    return weights, values, capacity


def knapsack_exhaustive(weights, values, capacity):
    """
    Exhaustive search: try every one of the 2^n subsets of items.
    Returns (best_value, best_subset).
    """
    n = len(weights)
    best_value = 0
    best_subset = None

    # itertools.product([0, 1], repeat=n) generates every combination of
    # "include item i" (1) / "exclude item i" (0) for i = 0 .. n-1
    for combo in itertools.product([0, 1], repeat=n):
        total_weight = sum(w for w, take in zip(weights, combo) if take)
        if total_weight <= capacity:
            total_value = sum(v for v, take in zip(values, combo) if take)
            if total_value > best_value:
                best_value = total_value
                best_subset = combo

    return best_value, best_subset


def run_benchmark(time_limit=30.0, n_start=3, seed=42):
    """
    Increase n starting from n_start, timing knapsack_exhaustive each time,
    until a run exceeds time_limit seconds. Returns the list of (n, time) pairs.
    """
    results = []
    n = n_start
    while True:
        weights, values, capacity = generate_instance(n, seed=seed + n)
        start = time.perf_counter()
        best_value, best_subset = knapsack_exhaustive(weights, values, capacity)
        elapsed = time.perf_counter() - start
        results.append((n, elapsed, best_value))
        print(f"n = {n:2d} | subsets = 2^{n} = {2**n:>10,} | "
              f"time = {elapsed:8.4f} s | best value = {best_value}")

        if elapsed > time_limit:
            print(f"\nStopping: n = {n} exceeded the {time_limit:.0f}s limit "
                  f"({elapsed:.2f}s).")
            break

        n += 1

    return results


if __name__ == "__main__":
    print("=" * 70)
    print("0/1 KNAPSACK - EXHAUSTIVE SEARCH BENCHMARK")
    print("=" * 70)
    results = run_benchmark(time_limit=30.0, n_start=3)

    solvable = [r for r in results if r[1] <= 30.0]
    largest_n = max(r[0] for r in solvable) if solvable else None

    print("\n" + "=" * 70)
    print("SUMMARY TABLE")
    print("=" * 70)
    print(f"{'n':>4} | {'2^n subsets':>15} | {'time (s)':>12}")
    print("-" * 40)
    for n, t, v in results:
        print(f"{n:>4} | {2**n:>15,} | {t:>12.4f}")

    print(f"\nLargest problem size n solved within 30s: n = {largest_n}")
