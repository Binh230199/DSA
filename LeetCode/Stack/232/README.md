# Intuition
Queue có tính chất FIFO (First In First Out), stack có tính chất LIFO (Last In First Out). Để implement queue bằng stack, cần reverse order của elements để element đầu tiên push sẽ được pop đầu tiên.

# Approach

## Approach 1: Two Stacks - Push Heavy
**Ý tưởng**: Luôn maintain queue order trong outStack, mọi push operation đều expensive.

**Cấu trúc dữ liệu**: 
- `inStack`: Temporary storage
- `outStack`: Maintain queue order (front at top)

**Operations**:
- **Push**: 
  1. Move tất cả elements từ outStack sang inStack
  2. Push new element vào inStack
  3. Move tất cả elements từ inStack về outStack
- **Pop/Peek**: Direct access outStack.top()

**Trade-off**: Push expensive O(n), pop/peek cheap O(1)

---

## Approach 2: Two Stacks - Pop Heavy (Amortized O(1)) ⭐
**Ý tưởng**: Lazy transfer - chỉ transfer khi cần thiết.

**Cấu trúc dữ liệu**:
- `inStack`: Chứa new elements (for push)
- `outStack`: Chứa old elements (for pop/peek)

**Operations**:
- **Push**: Simple inStack.push(x)
- **Pop/Peek**: 
  1. Nếu outStack rỗng, transfer tất cả từ inStack sang outStack
  2. Pop/peek từ outStack

**Amortized Analysis**:
- Mỗi element được move tối đa 2 lần (in -> out)
- Total cost cho n operations: O(n)
- Amortized cost per operation: O(1)

---

## Approach 3: One Stack with Recursion
**Ý tưởng**: Dùng recursion để access bottom element của stack.

**Operations**:
- **Push**: Simple st.push(x)
- **Pop/Peek**: 
  1. Recursively pop elements cho đến khi reach bottom
  2. Return bottom element
  3. Push back tất cả elements

**Nhược điểm**: O(n) cho mỗi pop/peek, recursion overhead

# Complexity
- Time complexity:
  - **Approach 1 (Push Heavy)**: $$O(n)$$ push, $$O(1)$$ pop/peek
  - **Approach 2 (Amortized)**: $$O(1)$$ push, Amortized $$O(1)$$ pop/peek
  - **Approach 3 (Recursive)**: $$O(1)$$ push, $$O(n)$$ pop/peek

- Space complexity: $$O(n)$$ for all approaches

# Code
```cpp []
// Approach 2: Two Stacks - Amortized O(1) (Recommended)
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
```

# Detailed Implementation Analysis

## Approach 2 - Amortized Analysis Deep Dive

### **Tại sao Amortized O(1)?**

**Worst Case Scenario**: 
- Push n elements: inStack = [1,2,3,...,n]
- Pop 1 element: Transfer all n elements to outStack

**Analysis**:
```
Operations sequence: push(1), push(2), ..., push(n), pop(), pop(), ..., pop()

Push phase: n operations, each O(1) = O(n) total
Pop phase: 
  - First pop: O(n) transfer + O(1) pop = O(n)
  - Next (n-1) pops: each O(1) = O(n-1) total

Total cost: O(n) + O(n) + O(n-1) = O(n)
Total operations: n + n = 2n
Amortized cost per operation: O(n) / 2n = O(1)
```

### **Key Insight**: 
Mỗi element được move tối đa 2 lần:
1. Push vào inStack
2. Transfer từ inStack sang outStack

### **Step by Step Example**:
```
push(1): inStack=[1], outStack=[]
push(2): inStack=[1,2], outStack=[]
push(3): inStack=[1,2,3], outStack=[]

pop(): 
  Transfer: inStack=[] -> outStack=[3,2,1]
  Pop: return 1, outStack=[3,2]

pop(): return 2, outStack=[3]  // O(1)
pop(): return 3, outStack=[]   // O(1)
```

## So sánh 3 approaches:

| Approach | Push | Pop | Peek | Best For | Notes |
|----------|------|-----|------|----------|-------|
| Push Heavy | O(n) | O(1) | O(1) | Read-heavy | Consistent performance |
| Amortized | O(1) | O(1)* | O(1)* | Balanced | *Amortized |
| Recursive | O(1) | O(n) | O(n) | Educational | High overhead |

**Recommendation**: Approach 2 (Amortized) - best overall performance

# Application in realworld

## 1. Task Scheduling System
```cpp
class TaskScheduler {
    MyQueue taskQueue;
    
    void addTask(int taskId) {
        taskQueue.push(taskId);  // O(1) - fast task addition
    }
    
    int processNextTask() {
        if (!taskQueue.empty()) {
            return taskQueue.pop();  // Amortized O(1)
        }
        return -1; // No tasks
    }
    
    int peekNextTask() {
        return taskQueue.peek();  // Check without processing
    }
};
```

## 2. Print Queue Implementation
```cpp
class PrintQueue {
    MyQueue printJobs;
    
    void submitPrintJob(int jobId) {
        printJobs.push(jobId);  // Add to end of queue
    }
    
    int processPrintJob() {
        return printJobs.pop();  // Process oldest job first
    }
    
    bool hasJobs() {
        return !printJobs.empty();
    }
};
```

## 3. Breadth-First Search (BFS)
```cpp
class BFSTraversal {
    MyQueue nodeQueue;
    
    void addNode(int nodeId) {
        nodeQueue.push(nodeId);
    }
    
    int getNextNode() {
        return nodeQueue.pop();  // FIFO order for BFS
    }
    
    bool hasMoreNodes() {
        return !nodeQueue.empty();
    }
};
```

## 4. Message Queue System
```cpp
class MessageQueue {
    MyQueue messages;
    
    void sendMessage(int messageId) {
        messages.push(messageId);  // Add to queue
    }
    
    int receiveMessage() {
        return messages.pop();  // Get oldest message
    }
    
    int previewMessage() {
        return messages.peek();  // Check without removing
    }
};
```

**Tại sao implement queue với stack?**
- **System constraints**: Khi chỉ có stack operations available
- **Understanding data structures**: Educational value
- **Memory efficiency**: Stack-based implementation có thể efficient hơn
- **Amortized analysis**: Practical example of amortized complexity

# Related problems
- 225. Implement Stack using Queues
- 155. Min Stack
- 622. Design Circular Queue
- 641. Design Circular Deque
- 933. Number of Recent Calls
