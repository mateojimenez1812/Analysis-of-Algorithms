#include <iostream>
#include <list>
using namespace std;

// std::list behaves like a stack when we always insert and remove
// from the same end. push_back/pop_back work on the back of the list
// in O(1), which is exactly what a stack needs (LIFO).
int main() {
    list<int> myList;

    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);

    cout << "Top element: " << myList.back() << endl;

    myList.pop_back();
    cout << "After pop, top element: " << myList.back() << endl;

    cout << "Remaining elements: ";
    for (int val : myList) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
