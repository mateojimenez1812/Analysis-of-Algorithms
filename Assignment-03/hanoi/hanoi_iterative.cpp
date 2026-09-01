#include <iostream>
#include <vector>
using namespace std;

// Moves the top disk between two pegs, respecting the rule that a
// bigger disk can never sit on top of a smaller one.
void moveTopDisk(vector<int>& pegX, vector<int>& pegY) {
    if (pegX.empty()) {
        pegX.push_back(pegY.back());
        pegY.pop_back();
    } else if (pegY.empty()) {
        pegY.push_back(pegX.back());
        pegX.pop_back();
    } else if (pegX.back() < pegY.back()) {
        pegY.push_back(pegX.back());
        pegX.pop_back();
    } else {
        pegX.push_back(pegY.back());
        pegY.pop_back();
    }
}

long long hanoiIterative(int n) {
    vector<int> A, B, C;
    for (int d = n; d >= 1; d--) A.push_back(d); // disk n at the bottom, disk 1 on top

    long long totalMoves = (1LL << n) - 1;
    long long moveCount = 0;
    bool evenDisks = (n % 2 == 0);

    // The order in which the pair of pegs is chosen at each of the
    // three cyclic steps depends on whether n is even or odd; this is
    // what makes every disk end up on peg C regardless of parity.
    for (long long i = 1; i <= totalMoves; i++) {
        int step = i % 3;
        if (evenDisks) {
            if (step == 1) moveTopDisk(A, B);
            else if (step == 2) moveTopDisk(A, C);
            else moveTopDisk(B, C);
        } else {
            if (step == 1) moveTopDisk(A, C);
            else if (step == 2) moveTopDisk(A, B);
            else moveTopDisk(B, C);
        }
        moveCount++;
    }

    return moveCount;
}

int main() {
    int n;
    cout << "Enter number of disks: ";
    cin >> n;

    long long moves = hanoiIterative(n);
    cout << "Total moves: " << moves << endl;
    return 0;
}
