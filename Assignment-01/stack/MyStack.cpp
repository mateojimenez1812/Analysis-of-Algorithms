#include <iostream>
#include <list>
#include <stdexcept>
using namespace std;

class MyStack {
private:
    list<int> data;

public:
    void push(int value) {
        data.push_back(value);
    }

    void pop() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        data.pop_back();
    }

    int top() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        return data.back();
    }

    bool isEmpty() {
        return data.empty();
    }

    int size() {
        return data.size();
    }
};

int main() {
    MyStack s;
    s.push(1);
    s.push(2);
    s.push(3);

    cout << "Top: " << s.top() << endl;
    s.pop();
    cout << "Top after pop: " << s.top() << endl;
    cout << "Size: " << s.size() << endl;

    return 0;
}
