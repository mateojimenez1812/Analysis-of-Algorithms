#include <iostream>
using namespace std;

void fibonacciIterative(int n) {
    long long prev = 0, curr = 1;
    cout << prev << " ";
    if (n == 0) return;
    cout << curr << " ";

    for (int i = 2; i <= n; i++) {
        long long next = prev + curr;
        cout << next << " ";
        prev = curr;
        curr = next;
    }
}

int main() {
    int n;
    cout << "Enter n (number of terms after T(0)): ";
    cin >> n;

    cout << "Fibonacci sequence: ";
    fibonacciIterative(n);
    cout << endl;

    return 0;
}
