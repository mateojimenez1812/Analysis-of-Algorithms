#include <iostream>
using namespace std;

int consecutiveGCD(int m, int n) {
    int t = min(m, n);
    while (t > 0) {
        if (m % t == 0 && n % t == 0) {
            return t;
        }
        t--;
    }
    return 1;
}

int main() {
    int m, n;
    cout << "Enter m and n: ";
    cin >> m >> n;
    cout << "gcd(" << m << ", " << n << ") = " << consecutiveGCD(m, n) << endl;
    return 0;
}
