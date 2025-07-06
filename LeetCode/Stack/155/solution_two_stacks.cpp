#include <iostream>
#include <stack>
#include <climits>
using namespace std;

// Approach 1: Two Stacks (Optimal)
class MinStack {
private:
    stack<int> dataStack;
    stack<int> minStack;
    
public:
    MinStack() {}
    
    void push(int val) {
        dataStack.push(val);
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }
    
    void pop() {
        if (dataStack.top() == minStack.top()) {
            minStack.pop();
        }
        dataStack.pop();
    }
    
    int top() {
        return dataStack.top();
    }
    
    int getMin() {
        return minStack.top();
    }
};

int main() {
    cout << "=== MinStack - Two Stacks Approach ===" << endl;
    cout << "Time: O(1) for all operations" << endl;
    cout << "Space: O(n) - worst case 2n" << endl << endl;
    
    MinStack minStack;
    
    // Test case from problem
    cout << "Operations:" << endl;
    
    minStack.push(-2);
    cout << "push(-2)" << endl;
    
    minStack.push(0);
    cout << "push(0)" << endl;
    
    minStack.push(-3);
    cout << "push(-3)" << endl;
    
    cout << "getMin() = " << minStack.getMin() << endl;  // -3
    
    minStack.pop();
    cout << "pop()" << endl;
    
    cout << "top() = " << minStack.top() << endl;        // 0
    
    cout << "getMin() = " << minStack.getMin() << endl;  // -2
    
    cout << "\n=== Additional Tests ===" << endl;
    
    MinStack ms2;
    ms2.push(5);
    ms2.push(3);
    ms2.push(7);
    ms2.push(1);
    
    cout << "After push [5,3,7,1]:" << endl;
    cout << "top() = " << ms2.top() << endl;       // 1
    cout << "getMin() = " << ms2.getMin() << endl; // 1
    
    ms2.pop();
    cout << "After pop():" << endl;
    cout << "top() = " << ms2.top() << endl;       // 7
    cout << "getMin() = " << ms2.getMin() << endl; // 3
    
    ms2.pop();
    cout << "After pop():" << endl;
    cout << "top() = " << ms2.top() << endl;       // 3
    cout << "getMin() = " << ms2.getMin() << endl; // 3
    
    return 0;
}
