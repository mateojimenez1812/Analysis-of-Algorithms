#include <iostream>
using namespace std;

// Linear Congruential Method: X(n+1) = (a * X(n) + c) mod m
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

int main() {
    // Same constants used by the ANSI C rand() implementation
    unsigned long long a = 1103515245;
    unsigned long long c = 12345;
    unsigned long long m = 2147483648ULL; // 2^31
    unsigned long long seed = 42;

    int n;
    cout << "Enter how many pseudo-random numbers to generate: ";
    cin >> n;

    LinearCongruentialGenerator lcg(a, c, m, seed);

    cout << "Generated numbers: ";
    int toPrint = min(n, 20); // avoid flooding the screen for large n
    for (int i = 0; i < n; i++) {
        unsigned long long value = lcg.next();
        if (i < toPrint) cout << value << " ";
    }
    if (n > toPrint) cout << "...";
    cout << endl;

    return 0;
}
