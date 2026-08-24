#include <iostream>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

vector<int> sieveOfEratosthenes(int n) {
    vector<int> A(n + 1, 1);
    A[0] = A[1] = 0;
    int limit = (int)sqrt((double)n);

    for (int p = 2; p <= limit; p++) {
        if (A[p] != 0) {
            for (int j = p * p; j <= n; j += p) {
                A[j] = 0;
            }
        }
    }

    vector<int> primes;
    for (int p = 2; p <= n; p++) {
        if (A[p] != 0) {
            primes.push_back(p);
        }
    }
    return primes;
}

map<int, int> primeFactorization(int num, const vector<int>& primes) {
    map<int, int> factors;
    for (int p : primes) {
        if (p > num) break;
        while (num % p == 0) {
            factors[p]++;
            num /= p;
        }
    }
    return factors;
}

int middleSchoolGCD(int m, int n) {
    int bigger = max(m, n);
    vector<int> primes = sieveOfEratosthenes(bigger);

    map<int, int> fm = primeFactorization(m, primes);
    map<int, int> fn = primeFactorization(n, primes);

    int result = 1;
    for (auto& pair : fm) {
        int prime = pair.first;
        if (fn.count(prime)) {
            int times = min(pair.second, fn[prime]);
            for (int i = 0; i < times; i++) {
                result *= prime;
            }
        }
    }
    return result;
}

int main() {
    int m, n;
    cout << "Enter m and n: ";
    cin >> m >> n;
    cout << "gcd(" << m << ", " << n << ") = " << middleSchoolGCD(m, n) << endl;
    return 0;
}
