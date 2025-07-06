#include <iostream>
#include <queue>
using namespace std;

// Approach 2: Two Queues - Pop Heavy
class MyStack {
private:
    queue<int> q1, q2;
    
public:
    MyStack() {}
    
    void push(int x) {
        q1.push(x);
    }
    
    int pop() {
        // Move all elements except last from q1 to q2
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }
        
        // Last element is our result
        int result = q1.front();
        q1.pop();
        
        // Swap q1 and q2
        swap(q1, q2);
        
        return result;
    }
    
    int top() {
        // Move all elements except last from q1 to q2
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }
        
        // Last element is our result
        int result = q1.front();
        q2.push(q1.front());
        q1.pop();
        
        // Swap q1 and q2
        swap(q1, q2);
        
        return result;
    }
    
    bool empty() {
        return q1.empty();
    }
};

int main() {
    cout << "Approach 2: Two Queues - Pop Heavy" << endl;
    cout << "Time: O(1) push, O(n) pop/top" << endl;
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
    cout << "push(2): q1=[1,2], q2=[]" << endl;
    
    stack2.push(3);
    cout << "push(3): q1=[1,2,3], q2=[]" << endl;
    
    cout << "Before pop: q1=[1,2,3], q2=[]" << endl;
    cout << "pop() = " << stack2.pop() << endl;  // 3
    cout << "After pop: q1=[1,2], q2=[]" << endl;
    
    return 0;
}
