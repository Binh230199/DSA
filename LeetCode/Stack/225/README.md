# Intuition
Stack có tính chất LIFO (Last In First Out), queue có tính chất FIFO (First In First Out). Để implement stack bằng queue, cần reverse order của elements trong queue.

# Approach

## Approach 1: Two Queues - Push Heavy
**Ý tưởng**: Luôn giữ elements theo stack order trong q1, q2 chỉ là temporary storage.

**Operations**:
- **Push**: 
  1. Push element vào q2
  2. Move tất cả elements từ q1 sang q2
  3. Swap q1 và q2
- **Pop/Top**: Direct access q1.front()
- **Empty**: Check q1.empty()

**Tại sao hoạt động?**
- Sau mỗi push, q1 luôn có elements theo stack order (newest first)
- Pop và top chỉ cần lấy từ front của q1

---

## Approach 2: Two Queues - Pop Heavy
**Ý tưởng**: Push đơn giản, pop phức tạp - move elements để expose last element.

**Operations**:
- **Push**: Simple q1.push(x)
- **Pop**:
  1. Move tất cả elements trừ last từ q1 sang q2
  2. Last element là result
  3. Swap q1 và q2
- **Top**: Tương tự pop nhưng keep element

**Trade-off**: Push nhanh nhưng pop/top chậm

---

## Approach 3: One Queue - Rotate Queue
**Ý tưởng**: Sử dụng rotation để đưa newest element lên front.

**Operations**:
- **Push**:
  1. Push element vào queue
  2. Rotate queue (size-1) lần để đưa new element lên front
- **Pop/Top**: Direct access queue.front()

**Rotation Logic**:
- Sau khi push element mới, queue = [old_elements, new_element]
- Rotate size-1 lần: queue = [new_element, old_elements]

# Complexity
- Time complexity:
  - **Approach 1 (Push Heavy)**: $$O(n)$$ push, $$O(1)$$ pop/top
  - **Approach 2 (Pop Heavy)**: $$O(1)$$ push, $$O(n)$$ pop/top
  - **Approach 3 (One Queue)**: $$O(n)$$ push, $$O(1)$$ pop/top

- Space complexity: $$O(n)$$ for all approaches

# Code
```cpp []
// Approach 1: Two Queues - Push Heavy (Recommended)
class MyStack {
private:
    queue<int> q1, q2;
    
public:
    MyStack() {}
    
    void push(int x) {
        q2.push(x);
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
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

// Approach 3: One Queue - Space Optimized
class MyStack {
private:
    queue<int> q;
    
public:
    MyStack() {}
    
    void push(int x) {
        int size = q.size();
        q.push(x);
        for (int i = 0; i < size; i++) {
            q.push(q.front());
            q.pop();
        }
    }
    
    int pop() {
        int top = q.front();
        q.pop();
        return top;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
};
```

# Detailed Implementation Analysis

## Approach 1 - Step by Step Walkthrough
**Example**: push(1), push(2), push(3), pop(), top()

### Push Operations:
```
push(1): 
  q2=[1], q1=[]
  Move: q2=[1], q1=[]
  Swap: q1=[1], q2=[]

push(2):
  q2=[2], q1=[1]
  Move: q2=[2,1], q1=[]
  Swap: q1=[2,1], q2=[]

push(3):
  q2=[3], q1=[2,1]
  Move: q2=[3,2,1], q1=[]
  Swap: q1=[3,2,1], q2=[]
```

**Final State**: q1=[3,2,1] (stack order)

### Pop/Top Operations:
```
pop(): return q1.front() = 3, q1=[2,1]
top(): return q1.front() = 2
```

## Approach 3 - Rotation Process
**Example**: push(1), push(2), push(3)

### Push Operations:
```
push(1): q=[1], size=0, no rotation needed

push(2): 
  q=[1,2], size=1
  Rotate 1 time: q=[2,1]

push(3):
  q=[2,1,3], size=2
  Rotate 2 times: 
    After 1st: q=[1,3,2]
    After 2nd: q=[3,2,1]
```

**Result**: q=[3,2,1] (stack order)

## So sánh 3 approaches:

| Approach | Push | Pop | Top | Space | Best For |
|----------|------|-----|-----|--------|----------|
| Push Heavy | O(n) | O(1) | O(1) | O(n) | Frequent pop/top |
| Pop Heavy | O(1) | O(n) | O(n) | O(n) | Frequent push |
| One Queue | O(n) | O(1) | O(1) | O(n) | Space efficiency |

**Recommendation**: Approach 1 (Push Heavy) - thường pop/top được gọi nhiều hơn push

# Application in realworld

## 1. Browser History Implementation
```cpp
class BrowserHistory {
    MyStack history;
    
    void visitPage(string url) {
        history.push(url.length()); // Push page identifier
    }
    
    string goBack() {
        if (!history.empty()) {
            int pageId = history.pop();
            return getPageById(pageId);
        }
        return "No history";
    }
};
```

## 2. Function Call Stack Simulation
```cpp
class CallStackSimulator {
    MyStack callStack;
    
    void functionCall(int functionId) {
        callStack.push(functionId);
    }
    
    int functionReturn() {
        return callStack.pop(); // Return to previous function
    }
    
    int getCurrentFunction() {
        return callStack.top();
    }
};
```

## 3. Expression Evaluation
```cpp
class ExpressionEvaluator {
    MyStack operandStack;
    
    void pushOperand(int value) {
        operandStack.push(value);
    }
    
    int applyOperation(char op) {
        int b = operandStack.pop();
        int a = operandStack.pop();
        int result = calculate(a, op, b);
        operandStack.push(result);
        return result;
    }
};
```

**Tại sao implement stack với queue?**
- **Educational**: Hiểu rõ data structure properties
- **System constraints**: Khi chỉ có queue available
- **Memory management**: Queue có thể efficient hơn trong một số systems

# Related problems
- 232. Implement Queue using Stacks
- 155. Min Stack
- 20. Valid Parentheses
- 1047. Remove All Adjacent Duplicates In String
- 150. Evaluate Reverse Polish Notation
