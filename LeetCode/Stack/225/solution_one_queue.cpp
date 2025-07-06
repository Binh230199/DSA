#include <iostream>
#include <queue>
using namespace std;

// Approach 3: One Queue - Rotate Queue
class MyStack {
private:
    queue<int> q;
    
public:
    MyStack() {}
    
    void push(int x) {
        int size = q.size();
        q.push(x);
        
        // Rotate the queue to make new element at front
        for (int i = 0; i < size; i++) {
            q.push(q.front());
            q.pop();
        }
    }
    
    int pop() {
        int top = q.front();
        q.pop();
        return top;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
};

int main() {
    cout << "Approach 3: One Queue - Rotate Queue" << endl;
    cout << "Time: O(n) push, O(1) pop/top/empty" << endl;
    cout << "Space: O(n)" << endl << endl;
    
    MyStack myStack;
    
    myStack.push(1);
    cout << "push(1)" << endl;
    
    myStack.push(2);
    cout << "push(2)" << endl;
    
    cout << "top() = " << myStack.top() << endl;    // 2
    cout << "pop() = " << myStack.pop() << endl;    // 2
    cout << "empty() = " << myStack.empty() << endl; // false
    
    cout << "\n=== Rotation Process ===" << endl;
    
    MyStack stack2;
    cout << "push(1): q=[1]" << endl;
    stack2.push(1);
    
    cout << "push(2):" << endl;
    cout << "  Add 2: q=[1,2]" << endl;
    cout << "  Rotate: q=[2,1]" << endl;
    stack2.push(2);
    
    cout << "push(3):" << endl;
    cout << "  Add 3: q=[2,1,3]" << endl;
    cout << "  Rotate 2 times: q=[3,2,1]" << endl;
    stack2.push(3);
    
    cout << "pop() = " << stack2.pop() << endl;  // 3
    cout << "After pop: q=[2,1]" << endl;
    
    return 0;
}
