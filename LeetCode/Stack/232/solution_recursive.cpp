#include <iostream>
#include <stack>
using namespace std;

// Approach 3: One Stack with Recursion
class MyQueue {
private:
    stack<int> st;
    
public:
    MyQueue() {}
    
    void push(int x) {
        st.push(x);
    }
    
    int pop() {
        if (st.size() == 1) {
            int result = st.top();
            st.pop();
            return result;
        }
        
        // Recursively remove bottom element
        int top = st.top();
        st.pop();
        int result = pop();
        st.push(top);
        return result;
    }
    
    int peek() {
        if (st.size() == 1) {
            return st.top();
        }
        
        // Recursively get bottom element
        int top = st.top();
        st.pop();
        int result = peek();
        st.push(top);
        return result;
    }
    
    bool empty() {
        return st.empty();
    }
};

int main() {
    cout << "Approach 3: One Stack with Recursion" << endl;
    cout << "Time: O(1) push, O(n) pop/peek" << endl;
    cout << "Space: O(n) - including recursion stack" << endl << endl;
    
    MyQueue myQueue;
    
    myQueue.push(1);
    cout << "push(1)" << endl;
    
    myQueue.push(2);
    cout << "push(2)" << endl;
    
    cout << "peek() = " << myQueue.peek() << endl;  // 1
    cout << "pop() = " << myQueue.pop() << endl;    // 1
    cout << "empty() = " << myQueue.empty() << endl; // false
    
    cout << "\n=== Recursion Process ===" << endl;
    
    MyQueue queue2;
    queue2.push(1);
    queue2.push(2);
    queue2.push(3);
    
    cout << "Stack state: [1,2,3] (top=3)" << endl;
    cout << "pop() recursion:" << endl;
    cout << "  pop(3) -> pop(2) -> pop(1) -> return 1" << endl;
    cout << "  push(2) -> push(3)" << endl;
    cout << "  Final: [2,3] (top=3)" << endl;
    
    cout << "Result: " << queue2.pop() << endl;  // 1
    
    return 0;
}
