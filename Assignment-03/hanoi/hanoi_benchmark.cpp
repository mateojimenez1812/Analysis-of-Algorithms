#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>
using namespace std;
using namespace std::chrono;

// --- Recursive version ---
void hanoiRecursive(int n, char from, char aux, char to, long long& moveCount) {
    if (n == 0) return;
    hanoiRecursive(n - 1, from, to, aux, moveCount);
    moveCount++;
    hanoiRecursive(n - 1, aux, from, to, moveCount);
}

// --- Iterative version ---
void moveTopDisk(vector<int>& pegX, vector<int>& pegY) {
    if (pegX.empty()) { pegX.push_back(pegY.back()); pegY.pop_back(); }
    else if (pegY.empty()) { pegY.push_back(pegX.back()); pegX.pop_back(); }
    else if (pegX.back() < pegY.back()) { pegY.push_back(pegX.back()); pegX.pop_back(); }
    else { pegX.push_back(pegY.back()); pegY.pop_back(); }
}

long long hanoiIterative(int n) {
    vector<int> A, B, C;
    for (int d = n; d >= 1; d--) A.push_back(d);

    long long totalMoves = (1LL << n) - 1;
    long long moveCount = 0;
    bool evenDisks = (n % 2 == 0);

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

volatile long long sink = 0; // prevents the optimizer from discarding the work as dead code

double median(vector<double> v) {
    sort(v.begin(), v.end());
    size_t mid = v.size() / 2;
    if (v.size() % 2 == 0) return (v[mid - 1] + v[mid]) / 2.0;
    return v[mid];
}

double timeRecursive(int n, int repeats) {
    vector<double> times;
    for (int r = 0; r < repeats; r++) {
        long long moveCount = 0;
        auto t1 = high_resolution_clock::now();
        hanoiRecursive(n, 'A', 'B', 'C', moveCount);
        auto t2 = high_resolution_clock::now();
        sink = moveCount;
        times.push_back(duration<double, milli>(t2 - t1).count());
    }
    return median(times);
}

double timeIterative(int n, int repeats) {
    vector<double> times;
    for (int r = 0; r < repeats; r++) {
        auto t1 = high_resolution_clock::now();
        long long moves = hanoiIterative(n);
        auto t2 = high_resolution_clock::now();
        sink = moves;
        times.push_back(duration<double, milli>(t2 - t1).count());
    }
    return median(times);
}

int main() {
    vector<int> sizes = {20, 22, 24, 26, 28, 30};
    int repeats = 9;

    cout << left << setw(6) << "n" << setw(14) << "moves"
         << setw(16) << "recursive(ms)" << setw(10) << "ratio"
         << setw(16) << "iterative(ms)" << setw(10) << "ratio" << endl;

    double prevRecTime = -1, prevIterTime = -1;

    for (int n : sizes) {
        long long moveCount = (1LL << n) - 1;
        double recTime = timeRecursive(n, repeats);
        double iterTime = timeIterative(n, repeats);

        double recRatio = (prevRecTime > 0) ? recTime / prevRecTime : 0.0;
        double iterRatio = (prevIterTime > 0) ? iterTime / prevIterTime : 0.0;

        cout << left << setw(6) << n << setw(14) << moveCount
             << setw(16) << fixed << setprecision(3) << recTime
             << setw(10) << setprecision(2) << recRatio
             << setw(16) << setprecision(3) << iterTime
             << setw(10) << setprecision(2) << iterRatio << endl;

        prevRecTime = recTime;
        prevIterTime = iterTime;
    }

    return 0;
}
