#include <iostream>
#include <stack>
using namespace std;

// Approach 1: Two Stacks - Push Heavy
class MyQueue {
private:
    stack<int> inStack;
    stack<int> outStack;
    
public:
    MyQueue() {}
    
    void push(int x) {
        // Move all elements from outStack to inStack
        while (!outStack.empty()) {
            inStack.push(outStack.top());
            outStack.pop();
        }
        
        // Push new element to inStack
        inStack.push(x);
        
        // Move all elements back to outStack
        while (!inStack.empty()) {
            outStack.push(inStack.top());
            inStack.pop();
        }
    }
    
    int pop() {
        int front = outStack.top();
        outStack.pop();
        return front;
    }
    
    int peek() {
        return outStack.top();
    }
    
    bool empty() {
        return outStack.empty();
    }
};

int main() {
    cout << "Approach 1: Two Stacks - Push Heavy" << endl;
    cout << "Time: O(n) push, O(1) pop/peek/empty" << endl;
    cout << "Space: O(n)" << endl << endl;
    
    MyQueue myQueue;
    
    myQueue.push(1);
    cout << "push(1)" << endl;
    
    myQueue.push(2);
    cout << "push(2)" << endl;
    
    cout << "peek() = " << myQueue.peek() << endl;  // 1
    cout << "pop() = " << myQueue.pop() << endl;    // 1
    cout << "empty() = " << myQueue.empty() << endl; // false
    
    cout << "\n=== Step by Step Analysis ===" << endl;
    
    MyQueue queue2;
    cout << "Initial: inStack=[], outStack=[]" << endl;
    
    queue2.push(1);
    cout << "push(1): inStack=[], outStack=[1]" << endl;
    
    queue2.push(2);
    cout << "push(2): inStack=[], outStack=[1,2] (top=1)" << endl;
    
    queue2.push(3);
    cout << "push(3): inStack=[], outStack=[1,2,3] (top=1)" << endl;
    
    cout << "pop() = " << queue2.pop() << endl;  // 1
    cout << "After pop: outStack=[2,3] (top=2)" << endl;
    
    cout << "peek() = " << queue2.peek() << endl;  // 2
    
    return 0;
}
