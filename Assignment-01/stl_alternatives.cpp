#include <iostream>
#include <stack>
#include <queue>
#include <deque>
using namespace std;

void stackExample() {
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    cout << "std::stack top: " << s.top() << endl;
    s.pop();
    cout << "std::stack top after pop: " << s.top() << endl;
}

void queueExample() {
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    cout << "std::queue front: " << q.front() << endl;
    q.pop();
    cout << "std::queue front after pop: " << q.front() << endl;
}

void dequeExample() {
    deque<int> d;
    d.push_back(1);
    d.push_front(0);
    d.push_back(2);

    cout << "std::deque contents: ";
    for (int val : d) {
        cout << val << " ";
    }
    cout << endl;

    d.pop_front();
    d.pop_back();
    cout << "After popping both ends, front: " << d.front() << endl;
}

int main() {
    cout << "--- std::stack ---" << endl;
    stackExample();

    cout << "\n--- std::queue ---" << endl;
    queueExample();

    cout << "\n--- std::deque ---" << endl;
    dequeExample();

    return 0;
}
