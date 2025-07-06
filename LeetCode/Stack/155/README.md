# Intuition
Cần lưu trữ minimum element và có thể truy cập trong O(1). Stack có tính chất LIFO, nên minimum có thể thay đổi khi pop. Ý tưởng: track minimum tại mỗi level của stack.

# Approach

## Approach 1: Two Stacks (Optimal)
**Ý tưởng cốt lõi**: Sử dụng 2 stack - một cho data, một cho minimum values.

**Cấu trúc dữ liệu**:
- `dataStack`: Stack chính chứa tất cả values
- `minStack`: Stack chứa minimum values tại mỗi level

**Operations**:
- **Push**: 
  1. Push value vào dataStack
  2. Nếu minStack rỗng hoặc value <= minStack.top(), push value vào minStack
- **Pop**:
  1. Nếu dataStack.top() == minStack.top(), pop cả 2 stack
  2. Else chỉ pop dataStack
- **Top**: Return dataStack.top()
- **GetMin**: Return minStack.top()

**Tại sao hiệu quả?**
- minStack luôn có minimum value của dataStack tại mỗi thời điểm
- Khi pop, minimum tự động rollback về previous minimum

---

## Approach 2: Single Stack with Pairs
**Ý tưởng**: Mỗi element lưu cùng với minimum value tại thời điểm đó.

**Cấu trúc**: Stack chứa `pair<int, int>` = `{value, min_so_far}`

**Operations**:
- **Push**: Push `{val, min(val, current_min)}`
- **Pop**: Pop pair từ stack
- **Top**: Return stack.top().first
- **GetMin**: Return stack.top().second

---

## Approach 3: Encode Technique (Space Optimized)
**Ý tưởng**: Encode minimum vào value để chỉ cần 1 stack.

**Encoding**: Khi push value < current_min:
1. Push `encoded = 2*val - current_min`
2. Update `current_min = val`

**Decoding**: Khi pop:
1. Nếu stack.top() < current_min: 
   - Actual value = current_min
   - Previous min = 2*current_min - stack.top()
2. Else: actual value = stack.top()

**Ưu điểm**: Chỉ cần 1 stack + 1 biến current_min

# Complexity
- Time complexity:
  - **Approach 1 (Two Stacks)**: $$O(1)$$ cho tất cả operations
  - **Approach 2 (Pairs)**: $$O(1)$$ cho tất cả operations  
  - **Approach 3 (Encode)**: $$O(1)$$ cho tất cả operations

- Space complexity:
  - **Approach 1**: $$O(n)$$ - worst case 2n space (2 stacks)
  - **Approach 2**: $$O(n)$$ - mỗi element cần 2 values
  - **Approach 3**: $$O(n)$$ - chỉ 1 stack + 1 biến

# Code
```cpp []
// Approach 1: Two Stacks (Optimal)
class MinStack {
private:
    stack<int> dataStack;
    stack<int> minStack;
    
public:
    MinStack() {}
    
    void push(int val) {
        dataStack.push(val);
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }
    
    void pop() {
        if (dataStack.top() == minStack.top()) {
            minStack.pop();
        }
        dataStack.pop();
    }
    
    int top() {
        return dataStack.top();
    }
    
    int getMin() {
        return minStack.top();
    }
};
```

# Application in realworld

## 1. Stock Price Monitoring
**Scenario**: Track stock prices và luôn biết lowest price trong session
```cpp
class StockMonitor {
    MinStack priceStack;
    
    void recordPrice(int price) {
        priceStack.push(price);
    }
    
    int getCurrentPrice() {
        return priceStack.top();
    }
    
    int getLowestPrice() {
        return priceStack.getMin(); // Lowest price so far
    }
};
```

## 2. Server Load Balancing
**Scenario**: Track server loads và route requests đến server có minimum load
```cpp
class LoadBalancer {
    MinStack loadStack;
    
    void updateLoad(int load) {
        loadStack.push(load);
    }
    
    int getMinimumLoad() {
        return loadStack.getMin();
    }
    
    bool shouldAcceptRequest() {
        return loadStack.getMin() < MAX_LOAD_THRESHOLD;
    }
};
```

## 3. Memory Usage Tracking
**Scenario**: Monitor memory usage với ability to rollback và track minimum
```cpp
class MemoryTracker {
    MinStack memoryStack;
    
    void allocateMemory(int size) {
        memoryStack.push(size);
    }
    
    void deallocateMemory() {
        memoryStack.pop();
    }
    
    int getLowestMemoryUsage() {
        return memoryStack.getMin();
    }
};
```

## 4. Temperature Monitoring System
**Scenario**: Track temperatures và alert khi xuống minimum
```cpp
class TempMonitor {
    MinStack tempStack;
    
    void recordTemperature(int temp) {
        tempStack.push(temp);
    }
    
    bool isFreezingAlert() {
        return tempStack.getMin() <= FREEZING_POINT;
    }
    
    int getLowestRecordedTemp() {
        return tempStack.getMin();
    }
};
```

**Tại sao MinStack phù hợp?**
- Cần track minimum values trong real-time
- O(1) operations cho high-frequency updates
- Undo/rollback functionality với stack operations

# Related problems
- 716. Max Stack
- 895. Maximum Frequency Stack  
- 1381. Design a Stack With Increment Operation
- 232. Implement Queue using Stacks
- 225. Implement Stack using Queues
