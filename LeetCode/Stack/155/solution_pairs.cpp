#include <iostream>
#include <stack>
using namespace std;

// Approach 2: Single Stack with Pairs
class MinStack {
private:
    stack<pair<int, int>> st; // {value, min_so_far}
    
public:
    MinStack() {}
    
    void push(int val) {
        if (st.empty()) {
            st.push({val, val});
        } else {
            int currentMin = min(val, st.top().second);
            st.push({val, currentMin});
        }
    }
    
    void pop() {
        st.pop();
    }
    
    int top() {
        return st.top().first;
    }
    
    int getMin() {
        return st.top().second;
    }
};

int main() {
    cout << "=== MinStack - Pairs Approach ===" << endl;
    cout << "Time: O(1) for all operations" << endl;
    cout << "Space: O(n) - each element stores 2 values" << endl << endl;
    
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
    
    cout << "\n=== Step by Step Analysis ===" << endl;
    
    MinStack ms2;
    cout << "Push 5: stack = [{5,5}]" << endl;
    ms2.push(5);
    cout << "Current min: " << ms2.getMin() << endl;
    
    cout << "Push 3: stack = [{5,5}, {3,3}]" << endl;
    ms2.push(3);
    cout << "Current min: " << ms2.getMin() << endl;
    
    cout << "Push 7: stack = [{5,5}, {3,3}, {7,3}]" << endl;
    ms2.push(7);
    cout << "Current min: " << ms2.getMin() << endl;
    
    cout << "Push 1: stack = [{5,5}, {3,3}, {7,3}, {1,1}]" << endl;
    ms2.push(1);
    cout << "Current min: " << ms2.getMin() << endl;
    
    cout << "Pop: stack = [{5,5}, {3,3}, {7,3}]" << endl;
    ms2.pop();
    cout << "Current min: " << ms2.getMin() << endl;
    
    return 0;
}
