#include <iostream>
#include <stack>
#include <climits>
using namespace std;

// Approach 3: Encode Technique (Space Optimized)
class MinStack {
private:
    stack<long long> st;
    long long minVal;
    
public:
    MinStack() : minVal(LLONG_MAX) {}
    
    void push(int val) {
        if (st.empty()) {
            st.push(val);
            minVal = val;
        } else {
            if (val < minVal) {
                // Encode: push 2*val - minVal
                st.push(2LL * val - minVal);
                minVal = val;
            } else {
                st.push(val);
            }
        }
    }
    
    void pop() {
        if (st.empty()) return;
        
        long long topVal = st.top();
        st.pop();
        
        if (topVal < minVal) {
            // Decode: restore previous min
            minVal = 2 * minVal - topVal;
        }
    }
    
    int top() {
        long long topVal = st.top();
        if (topVal < minVal) {
            return minVal;  // Actual value is current min
        }
        return topVal;
    }
    
    int getMin() {
        return minVal;
    }
};

int main() {
    cout << "=== MinStack - Encode Technique ===" << endl;
    cout << "Time: O(1) for all operations" << endl;
    cout << "Space: O(n) - single stack + 1 variable" << endl << endl;
    
    MinStack minStack;
    
    // Test case from problem
    cout << "Operations with encoding:" << endl;
    
    minStack.push(-2);
    cout << "push(-2) -> minVal = -2" << endl;
    
    minStack.push(0);
    cout << "push(0) -> normal push" << endl;
    
    minStack.push(-3);
    cout << "push(-3) -> encode: 2*(-3) - (-2) = -4, minVal = -3" << endl;
    
    cout << "getMin() = " << minStack.getMin() << endl;  // -3
    
    minStack.pop();
    cout << "pop() -> decode: minVal = 2*(-3) - (-4) = -2" << endl;
    
    cout << "top() = " << minStack.top() << endl;        // 0
    
    cout << "getMin() = " << minStack.getMin() << endl;  // -2
    
    cout << "\n=== Encoding Logic Explanation ===" << endl;
    cout << "When push value < current_min:" << endl;
    cout << "1. Push encoded = 2*val - current_min" << endl;
    cout << "2. Update current_min = val" << endl;
    cout << "3. encoded < val (always true)" << endl;
    cout << "\nWhen pop encoded value:" << endl;
    cout << "1. If stack.top() < current_min: it's encoded" << endl;
    cout << "2. Actual value = current_min" << endl;
    cout << "3. Previous min = 2*current_min - stack.top()" << endl;
    
    cout << "\n=== Test with positive numbers ===" << endl;
    
    MinStack ms2;
    ms2.push(5);
    cout << "push(5) -> minVal = 5" << endl;
    
    ms2.push(3);
    cout << "push(3) -> encode: 2*3 - 5 = 1, minVal = 3" << endl;
    
    ms2.push(7);
    cout << "push(7) -> normal push" << endl;
    
    ms2.push(1);
    cout << "push(1) -> encode: 2*1 - 3 = -1, minVal = 1" << endl;
    
    cout << "getMin() = " << ms2.getMin() << endl;  // 1
    
    ms2.pop();
    cout << "pop() -> decode: minVal = 2*1 - (-1) = 3" << endl;
    
    cout << "getMin() = " << ms2.getMin() << endl;  // 3
    
    return 0;
}
