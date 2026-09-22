/*
 * Analysis of Algorithms - Lab 05 - Problem 2
 * Generate 10,000,000 random numbers, then locate a key using both
 * Binary Search and Interpolation Search, measuring and reporting the
 * execution time of each search.
 *
 * Note: both Binary Search and Interpolation Search require the array to
 * be SORTED beforehand, so the array is sorted once after generation
 * (sorting time is reported separately and is not counted as part of
 * either search's execution time).
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

const long long N = 10000000; // ten million

// ---- Binary Search ----
// Returns the index of 'key' in a sorted array, or -1 if not found.
long long binarySearch(const vector<int>& arr, int key) {
    long long low = 0, high = (long long)arr.size() - 1;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// ---- Interpolation Search ----
// Like binary search, but estimates the probe position assuming the
// data is uniformly distributed, using linear interpolation between
// the current low and high bounds instead of a plain midpoint.
long long interpolationSearch(const vector<int>& arr, int key) {
    long long low = 0, high = (long long)arr.size() - 1;

    while (low <= high && key >= arr[low] && key <= arr[high]) {
        if (low == high) {
            if (arr[low] == key) return low;
            return -1;
        }

        // Probe position estimated by linear interpolation
        long long pos = low + (long long)(
            (double)(high - low) * (double)(key - arr[low]) /
            (double)(arr[high] - arr[low])
        );

        if (arr[pos] == key) return pos;
        else if (arr[pos] < key) low = pos + 1;
        else high = pos - 1;
    }
    return -1;
}

int main() {
    vector<int> arr(N);

    // Generate N random numbers using a uniform distribution.
    mt19937 rng(42); // fixed seed for reproducibility
    uniform_int_distribution<int> dist(0, 100000000);

    for (long long i = 0; i < N; i++) {
        arr[i] = dist(rng);
    }

    // Sort is a prerequisite for both search algorithms.
    auto sortStart = high_resolution_clock::now();
    sort(arr.begin(), arr.end());
    auto sortEnd = high_resolution_clock::now();
    double sortMs = duration<double, milli>(sortEnd - sortStart).count();

    // A single search finishes in a fraction of a microsecond, which is
    // too small to measure reliably against system noise. To get a stable
    // reading, each search is repeated many times over a set of different
    // keys (spread across the array) and the total/average time is reported.
    const int REPETITIONS = 100000;
    vector<int> keys = {
        arr[0],                 // minimum
        arr[N / 4],              // first quartile
        arr[N / 2],               // median
        arr[(3 * N) / 4],          // third quartile
        arr[N - 1]                  // maximum
    };

    double bTotalMs = 0.0, iTotalMs = 0.0;
    long long bChecksum = 0, iChecksum = 0; // prevents the compiler from optimizing the loop away

    auto bStart = high_resolution_clock::now();
    for (int r = 0; r < REPETITIONS; r++) {
        for (int key : keys) {
            bChecksum += binarySearch(arr, key);
        }
    }
    auto bEnd = high_resolution_clock::now();
    bTotalMs = duration<double, milli>(bEnd - bStart).count();

    auto iStart = high_resolution_clock::now();
    for (int r = 0; r < REPETITIONS; r++) {
        for (int key : keys) {
            iChecksum += interpolationSearch(arr, key);
        }
    }
    auto iEnd = high_resolution_clock::now();
    iTotalMs = duration<double, milli>(iEnd - iStart).count();

    long long totalSearches = (long long)REPETITIONS * keys.size();
    double bAvgUs = (bTotalMs * 1000.0) / (double)totalSearches;
    double iAvgUs = (iTotalMs * 1000.0) / (double)totalSearches;

    cout << fixed << setprecision(6);
    cout << "Array size: " << N << " elements" << endl;
    cout << "Sorting time: " << sortMs << " ms" << endl;
    cout << "Total searches per algorithm: " << totalSearches
         << " (" << keys.size() << " keys x " << REPETITIONS << " repetitions)" << endl << endl;

    cout << "Binary Search:" << endl;
    cout << "  Total time: " << bTotalMs << " ms" << endl;
    cout << "  Average time per search: " << bAvgUs << " microseconds" << endl << endl;

    cout << "Interpolation Search:" << endl;
    cout << "  Total time: " << iTotalMs << " ms" << endl;
    cout << "  Average time per search: " << iAvgUs << " microseconds" << endl << endl;

    // Silent use of checksums so the compiler cannot eliminate the search loops
    if (bChecksum == -12345 && iChecksum == -12345) {
        cout << "Unreachable" << endl;
    }

    return 0;
}
