#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Simple Array Implementation
class CustomStack {
private:
    vector<int> stack;
    int maxSize;
    
public:
    CustomStack(int maxSize) : maxSize(maxSize) {}
    
    void push(int x) {
        if (stack.size() < maxSize) {
            stack.push_back(x);
        }
    }
    
    int pop() {
        if (stack.empty()) {
            return -1;
        }
        int top = stack.back();
        stack.pop_back();
        return top;
    }
    
    void increment(int k, int val) {
        int limit = min(k, (int)stack.size());
        for (int i = 0; i < limit; i++) {
            stack[i] += val;
        }
    }
};

int main() {
    cout << "Approach 1: Simple Array Implementation" << endl;
    cout << "Time: O(1) push/pop, O(k) increment" << endl;
    cout << "Space: O(maxSize)" << endl << endl;
    
    CustomStack stk(3);
    
    stk.push(1);           // [1]
    stk.push(2);           // [1,2]
    cout << stk.pop() << endl;  // 2, stack: [1]
    stk.push(2);           // [1,2]
    stk.push(3);           // [1,2,3]
    stk.push(4);           // [1,2,3] - không thêm được
    stk.increment(5, 100); // [101,102,103]
    stk.increment(2, 100); // [201,202,103]
    cout << stk.pop() << endl;  // 103
    cout << stk.pop() << endl;  // 202
    cout << stk.pop() << endl;  // 201
    cout << stk.pop() << endl;  // -1
    
    return 0;
}
