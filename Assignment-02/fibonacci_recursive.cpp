#include <iostream>
using namespace std;

long long fibonacciRecursive(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

int main() {
    int n;
    cout << "Enter n (number of terms after T(0)): ";
    cin >> n;

    cout << "Fibonacci sequence: ";
    for (int i = 0; i <= n; i++) {
        cout << fibonacciRecursive(i) << " ";
    }
    cout << endl;

    return 0;
}
