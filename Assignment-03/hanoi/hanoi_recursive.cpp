#include <iostream>
using namespace std;

long long moveCount = 0;

void hanoiRecursive(int n, char from, char aux, char to) {
    if (n == 0) return;
    hanoiRecursive(n - 1, from, to, aux);
    moveCount++;
    hanoiRecursive(n - 1, aux, from, to);
}

int main() {
    int n;
    cout << "Enter number of disks: ";
    cin >> n;

    moveCount = 0;
    hanoiRecursive(n, 'A', 'B', 'C');

    cout << "Total moves: " << moveCount << endl;
    return 0;
}
