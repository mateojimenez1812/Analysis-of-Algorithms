#include <iostream>
using namespace std;

int euclidGCD(int m, int n) {
    while (n != 0) {
        int r = m % n;
        m = n;
        n = r;
    }
    return m;
}

int main() {
    int m, n;
    cout << "Enter m and n: ";
    cin >> m >> n;
    cout << "gcd(" << m << ", " << n << ") = " << euclidGCD(m, n) << endl;
    return 0;
}
