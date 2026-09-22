/*
 * Analysis of Algorithms - Lab 05 - Problem 1
 * Insertion Sort applied to a randomly generated array of alphabetic characters.
 *
 * No structural adjustment to the classic Insertion Sort algorithm is required
 * to sort characters instead of integers: in C/C++, 'char' is an integral type,
 * and the standard comparison operators (<, >, <=, >=) are already defined for
 * it based on the underlying ASCII code. Since Insertion Sort only relies on
 * pairwise comparisons and shifting, the exact same algorithm that sorts an
 * array of ints works unchanged on an array of chars.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Classic Insertion Sort, generic-looking but specialized to char here.
void insertionSort(char arr[], int n) {
    for (int i = 1; i < n; i++) {
        char key = arr[i];
        int j = i - 1;

        // Shift elements of arr[0..i-1] that are greater than key
        // one position ahead of their current position.
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void printArray(const char arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i != n - 1) cout << ' ';
    }
    cout << endl;
}

int main() {
    const int N = 20; // small size so the before/after arrays are readable
    char arr[N];

    srand(static_cast<unsigned int>(time(nullptr)));

    // Generate random lowercase letters 'a' .. 'z'
    for (int i = 0; i < N; i++) {
        arr[i] = 'a' + (rand() % 26);
    }

    cout << "Original array (unsorted):" << endl;
    printArray(arr, N);

    insertionSort(arr, N);

    cout << "Sorted array (ascending):" << endl;
    printArray(arr, N);

    return 0;
}
