# Intuition
Cần implement một stack với giới hạn size và có thể increment k elements từ bottom. Vấn đề chính là làm sao để increment hiệu quả mà không cần duyệt qua tất cả elements.

# Approach

## Approach 1: Simple Array Implementation
Sử dụng vector để lưu stack, implement straightforward:
- `push`: Thêm vào cuối nếu chưa đầy
- `pop`: Lấy từ cuối
- `increment`: Duyệt k elements đầu và tăng val

## Approach 2: Lazy Propagation (Optimal)
Tối ưu increment operation bằng lazy propagation:
- `stack`: Lưu giá trị gốc
- `lazy`: Lưu increment cần apply cho từng position
- `increment`: Chỉ mark lazy value tại position k-1
- `pop`: Apply lazy value và propagate xuống element trước đó

**Lazy Propagation Logic**:
- Khi increment(k, val): chỉ set `lazy[k-1] += val`
- Khi pop element tại index i: 
  - Kết quả = `stack[i] + lazy[i]`
  - Propagate: `lazy[i-1] += lazy[i]`
  - Reset: `lazy[i] = 0`

**Tại sao hoạt động?**
- Increment chỉ ảnh hưởng đến k elements từ bottom
- Khi pop element thứ i, lazy[i] chứa tất cả increment operations ảnh hưởng đến nó
- Propagate lazy[i] xuống lazy[i-1] để ensure correctness

# Complexity
- Time complexity:
  - **Approach 1**: $$O(1)$$ push/pop, $$O(k)$$ increment
  - **Approach 2**: $$O(1)$$ for all operations

- Space complexity: $$O(maxSize)$$ for both approaches

# Code
```cpp []
// Approach 1: Simple Implementation
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
        if (stack.empty()) return -1;
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

// Approach 2: Lazy Propagation (Optimal)
class CustomStack {
private:
    vector<int> stack;
    vector<int> lazy;
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
        if (stack.empty()) return -1;
        
        int idx = stack.size() - 1;
        int result = stack[idx] + lazy[idx];
        
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
```

# Detailed Implementation Analysis

## Approach 2 - Lazy Propagation Walkthrough
**Example**: MaxSize=3, Operations: push(1), push(2), push(3), increment(2,100), increment(3,50), pop(), pop(), pop()

### Operations:
```
push(1): stack=[1], lazy=[0,0,0]
push(2): stack=[1,2], lazy=[0,0,0]  
push(3): stack=[1,2,3], lazy=[0,0,0]

increment(2,100): stack=[1,2,3], lazy=[0,100,0]
  - Chỉ set lazy[1] = 100 (affect 2 elements từ bottom)

increment(3,50): stack=[1,2,3], lazy=[0,100,50]
  - Set lazy[2] = 50 (affect 3 elements từ bottom)

pop(): idx=2, result = 3 + 50 = 53
  - Propagate: lazy[1] += lazy[2] = 100 + 50 = 150
  - Reset: lazy[2] = 0
  - stack=[1,2], lazy=[0,150,0]

pop(): idx=1, result = 2 + 150 = 152
  - Propagate: lazy[0] += lazy[1] = 0 + 150 = 150
  - Reset: lazy[1] = 0  
  - stack=[1], lazy=[150,0,0]

pop(): idx=0, result = 1 + 150 = 151
  - No propagation (idx=0)
  - stack=[], lazy=[0,0,0]
```

**Kết quả**: 53, 152, 151

## So sánh 2 approaches:

| Approach | Push | Pop | Increment | Pros | Cons |
|----------|------|-----|-----------|------|------|
| Simple | O(1) | O(1) | O(k) | Easy to understand | Slow increment |
| Lazy Propagation | O(1) | O(1) | O(1) | All O(1) operations | Complex logic |

# Application in realworld

## 1. Undo Operations in Text Editor
```cpp
class TextEditor {
    CustomStack history;
    
    void bulkEdit(int lines, string change) {
        // Apply change to bottom k lines
        history.increment(lines, change.length());
    }
};
```

## 2. Batch Processing with Incremental Updates
```cpp
class BatchProcessor {
    CustomStack processingQueue;
    
    void applyBatchUpdate(int batchSize, int priority) {
        // Increase priority for first batchSize items
        processingQueue.increment(batchSize, priority);
    }
};
```

## 3. Game Score System
```cpp
class GameScoring {
    CustomStack playerScores;
    
    void bonusForTopPlayers(int k, int bonus) {
        // Give bonus to bottom k players (early joiners)
        playerScores.increment(k, bonus);
    }
};
```

# Related problems
- 155. Min Stack
- 716. Max Stack  
- 895. Maximum Frequency Stack
- 1472. Design Browser History
- 1190. Reverse Substrings Between Each Pair of Parentheses
