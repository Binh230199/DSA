#include <iostream>
#include <queue>
using namespace std;

// Approach 1: Two Queues - Push Heavy
class MyStack {
private:
    queue<int> q1, q2;
    
public:
    MyStack() {}
    
    void push(int x) {
        // Push to q2
        q2.push(x);
        
        // Move all elements from q1 to q2
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        
        // Swap q1 and q2
        swap(q1, q2);
    }
    
    int pop() {
        int top = q1.front();
        q1.pop();
        return top;
    }
    
    int top() {
        return q1.front();
    }
    
    bool empty() {
        return q1.empty();
    }
};

int main() {
    cout << "Approach 1: Two Queues - Push Heavy" << endl;
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
    
    cout << "\n=== Step by Step Analysis ===" << endl;
    
    MyStack stack2;
    cout << "Initial: q1=[], q2=[]" << endl;
    
    stack2.push(1);
    cout << "push(1): q1=[1], q2=[]" << endl;
    
    stack2.push(2);
    cout << "push(2): q1=[2,1], q2=[]" << endl;
    
    stack2.push(3);
    cout << "push(3): q1=[3,2,1], q2=[]" << endl;
    
    cout << "pop() = " << stack2.pop() << endl;  // 3
    cout << "After pop: q1=[2,1], q2=[]" << endl;
    
    cout << "top() = " << stack2.top() << endl;  // 2
    
    return 0;
}
