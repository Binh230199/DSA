#include <iostream>
#include <stack>
using namespace std;

// Approach 2: Two Stacks - Pop Heavy (Amortized O(1))
class MyQueue {
private:
    stack<int> inStack;   // For push operations
    stack<int> outStack;  // For pop/peek operations
    
public:
    MyQueue() {}
    
    void push(int x) {
        inStack.push(x);
    }
    
    int pop() {
        // Ensure outStack has elements
        if (outStack.empty()) {
            while (!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }
        
        int front = outStack.top();
        outStack.pop();
        return front;
    }
    
    int peek() {
        // Ensure outStack has elements
        if (outStack.empty()) {
            while (!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }
        
        return outStack.top();
    }
    
    bool empty() {
        return inStack.empty() && outStack.empty();
    }
};

int main() {
    cout << "Approach 2: Two Stacks - Pop Heavy (Amortized O(1))" << endl;
    cout << "Time: O(1) push, Amortized O(1) pop/peek" << endl;
    cout << "Space: O(n)" << endl << endl;
    
    MyQueue myQueue;
    
    myQueue.push(1);
    cout << "push(1)" << endl;
    
    myQueue.push(2);
    cout << "push(2)" << endl;
    
    cout << "peek() = " << myQueue.peek() << endl;  // 1
    cout << "pop() = " << myQueue.pop() << endl;    // 1
    cout << "empty() = " << myQueue.empty() << endl; // false
    
    cout << "\n=== Amortized Analysis ===" << endl;
    
    MyQueue queue2;
    
    // Push operations: O(1) each
    queue2.push(1);
    cout << "push(1): inStack=[1], outStack=[]" << endl;
    
    queue2.push(2);
    cout << "push(2): inStack=[1,2], outStack=[]" << endl;
    
    queue2.push(3);
    cout << "push(3): inStack=[1,2,3], outStack=[]" << endl;
    
    // First pop: O(n) - transfer all elements
    cout << "First pop() - Transfer phase:" << endl;
    cout << "  Move inStack to outStack: outStack=[3,2,1]" << endl;
    cout << "  pop() = " << queue2.pop() << endl;  // 1
    cout << "  Result: inStack=[], outStack=[3,2]" << endl;
    
    // Subsequent pops: O(1) each
    cout << "Second pop() = " << queue2.pop() << endl;  // 2
    cout << "Third pop() = " << queue2.pop() << endl;   // 3
    
    cout << "\nAmortized Analysis:" << endl;
    cout << "- Each element is moved at most twice (in -> out)" << endl;
    cout << "- Total cost for n operations: O(n)" << endl;
    cout << "- Amortized cost per operation: O(1)" << endl;
    
    return 0;
}
