#include <iostream>
#include <vector>
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

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    vector<int> primes = sieveOfEratosthenes(n);
    cout << "Primes up to " << n << ": ";
    for (int p : primes) {
        cout << p << " ";
    }
    cout << endl;
    return 0;
}
