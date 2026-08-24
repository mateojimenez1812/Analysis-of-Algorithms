#include <iostream>
#include <list>
using namespace std;

// A list behaves like a queue when elements are added at the back
// and removed from the front. Both push_back and pop_front run in
// O(1) on a std::list, which gives the FIFO behavior of a queue.
int main() {
    list<int> myList;

    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);

    cout << "Front element: " << myList.front() << endl;

    myList.pop_front();
    cout << "After dequeue, front element: " << myList.front() << endl;

    cout << "Remaining elements: ";
    for (int val : myList) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
