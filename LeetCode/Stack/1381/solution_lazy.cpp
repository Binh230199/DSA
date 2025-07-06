#include <iostream>
#include <vector>
using namespace std;

// Approach 2: Lazy Propagation - Optimized Increment
class CustomStack {
private:
    vector<int> stack;
    vector<int> lazy;  // lazy[i] = increment to apply to stack[i]
    int maxSize;
    
public:
    CustomStack(int maxSize) : maxSize(maxSize) {
        lazy.resize(maxSize, 0);
    }
    
    void push(int x) {
        if (stack.size() < maxSize) {
            stack.push_back(x);
        }
    }
    
    int pop() {
        if (stack.empty()) {
            return -1;
        }
        
        int idx = stack.size() - 1;
        int result = stack[idx] + lazy[idx];
        
        // Propagate lazy value to previous element
        if (idx > 0) {
            lazy[idx - 1] += lazy[idx];
        }
        
        lazy[idx] = 0;
        stack.pop_back();
        return result;
    }
    
    void increment(int k, int val) {
        int limit = min(k, (int)stack.size()) - 1;
        if (limit >= 0) {
            lazy[limit] += val;
        }
    }
};

int main() {
    cout << "Approach 2: Lazy Propagation - Optimized" << endl;
    cout << "Time: O(1) for all operations" << endl;
    cout << "Space: O(maxSize)" << endl << endl;
    
    CustomStack stk(3);
    
    stk.push(1);           // [1]
    stk.push(2);           // [1,2]
    cout << stk.pop() << endl;  // 2, stack: [1]
    stk.push(2);           // [1,2]
    stk.push(3);           // [1,2,3]
    stk.push(4);           // [1,2,3] - không thêm được
    stk.increment(5, 100); // lazy propagation
    stk.increment(2, 100); // lazy propagation
    cout << stk.pop() << endl;  // 103
    cout << stk.pop() << endl;  // 202
    cout << stk.pop() << endl;  // 201
    cout << stk.pop() << endl;  // -1
    
    return 0;
}
