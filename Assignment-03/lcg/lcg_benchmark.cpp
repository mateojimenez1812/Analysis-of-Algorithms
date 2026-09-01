#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>
using namespace std;
using namespace std::chrono;

class LinearCongruentialGenerator {
private:
    unsigned long long a, c, m, seed;

public:
    LinearCongruentialGenerator(unsigned long long a_, unsigned long long c_,
                                 unsigned long long m_, unsigned long long seed_)
        : a(a_), c(c_), m(m_), seed(seed_) {}

    unsigned long long next() {
        seed = (a * seed + c) % m;
        return seed;
    }
};

volatile unsigned long long sink = 0;

double median(vector<double> v) {
    sort(v.begin(), v.end());
    size_t mid = v.size() / 2;
    if (v.size() % 2 == 0) return (v[mid - 1] + v[mid]) / 2.0;
    return v[mid];
}

double timeGeneration(long long n, int repeats) {
    vector<double> times;
    for (int r = 0; r < repeats; r++) {
        LinearCongruentialGenerator lcg(1103515245ULL, 12345ULL, 2147483648ULL, 42ULL);
        auto t1 = high_resolution_clock::now();
        unsigned long long last = 0;
        for (long long i = 0; i < n; i++) {
            last = lcg.next();
        }
        auto t2 = high_resolution_clock::now();
        sink = last;
        times.push_back(duration<double, milli>(t2 - t1).count());
    }
    return median(times);
}

int main() {
    vector<long long> sizes = {1000000, 2000000, 4000000, 8000000, 16000000, 32000000};
    int repeats = 7;

    cout << left << setw(14) << "n" << setw(16) << "time(ms)" << setw(10) << "ratio" << endl;

    double prevTime = -1;
    for (long long n : sizes) {
        double t = timeGeneration(n, repeats);
        double ratio = (prevTime > 0) ? t / prevTime : 0.0;
        cout << left << setw(14) << n << setw(16) << fixed << setprecision(3) << t
             << setw(10) << setprecision(2) << ratio << endl;
        prevTime = t;
    }

    return 0;
}
