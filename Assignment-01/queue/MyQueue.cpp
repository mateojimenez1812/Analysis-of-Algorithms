#include <iostream>
#include <list>
#include <stdexcept>
using namespace std;

class MyQueue {
private:
    list<int> data;

public:
    void enqueue(int value) {
        data.push_back(value);
    }

    void dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        data.pop_front();
    }

    int front() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        return data.front();
    }

    bool isEmpty() {
        return data.empty();
    }

    int size() {
        return data.size();
    }
};

int main() {
    MyQueue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    cout << "Front: " << q.front() << endl;
    q.dequeue();
    cout << "Front after dequeue: " << q.front() << endl;
    cout << "Size: " << q.size() << endl;

    return 0;
}
