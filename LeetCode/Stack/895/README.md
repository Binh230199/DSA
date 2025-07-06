# Intuition
Stack có tính chất LIFO, nên element nào được push sau cùng sẽ được pop trước. Với FreqStack, ta cần pop element có frequency cao nhất, nếu tie thì pop element được push gần nhất.

# Approach

## Approach 1: Frequency Buckets (Optimal) ⭐
**Ý tưởng cốt lõi**: Thay vì dùng 1 stack duy nhất, ta tạo nhiều stack - mỗi stack chứa tất cả elements có cùng frequency.

**Cấu trúc dữ liệu**:
- `freq[val]`: HashMap lưu frequency hiện tại của value
- `buckets[f]`: HashMap lưu stack chứa tất cả values có frequency = f
- `maxFreq`: Track frequency cao nhất hiện tại

**Push Operation**:
1. Tăng frequency: `freq[val]++`
2. Đưa value vào bucket tương ứng: `buckets[freq[val]].push(val)`
3. Cập nhật maxFreq: `maxFreq = max(maxFreq, freq[val])`

**Pop Operation**:
1. Lấy element từ bucket có frequency cao nhất: `buckets[maxFreq].top()`
2. Remove element khỏi bucket: `buckets[maxFreq].pop()`
3. Giảm frequency: `freq[val]--`
4. Nếu bucket rỗng, giảm maxFreq: `if (buckets[maxFreq].empty()) maxFreq--`

**Tại sao hiệu quả?**
- Không cần tìm kiếm - trực tiếp access bucket có maxFreq
- Stack tự động maintain thứ tự LIFO cho elements cùng frequency

---

## Approach 2: Naive - Linear Search 
**Ý tưởng**: Lưu tất cả elements với timestamp, mỗi lần pop thì scan toàn bộ để tìm element phù hợp.

**Cấu trúc dữ liệu**:
- `elements`: Vector lưu `{value, timestamp}`
- `freq`: HashMap lưu frequency
- `timestamp`: Counter để track thứ tự push

**Push Operation**:
1. Tăng frequency: `freq[val]++`
2. Lưu element với timestamp: `elements.push_back({val, timestamp++})`

**Pop Operation**:
1. Scan toàn bộ `elements` để tìm element có:
   - Frequency cao nhất
   - Nếu tie, timestamp cao nhất (push gần nhất)
2. Mark element đó là deleted (set value = -1)
3. Giảm frequency

**Nhược điểm**: O(n) cho mỗi pop operation vì phải scan toàn bộ

---

## Approach 3: Priority Queue (Max Heap)
**Ý tưởng**: Dùng heap để tự động sort elements theo priority (frequency, timestamp).

**Cấu trúc dữ liệu**:
- `pq`: Priority queue chứa `{val, freq, timestamp}`
- `freq`: HashMap lưu frequency hiện tại
- Custom comparator: Element có freq cao hơn có priority cao hơn, tie break bằng timestamp

**Push Operation**:
1. Tăng frequency: `freq[val]++`
2. Push vào heap: `pq.push({val, freq[val], timestamp++})`

**Pop Operation**:
1. Lấy top element từ heap
2. **Kiểm tra tính hợp lệ**: `if (top.freq == freq[top.val])` 
   - Vì heap có thể chứa stale entries (elements đã bị pop nhưng vẫn còn trong heap)
3. Nếu valid, giảm frequency và return
4. Nếu invalid, tiếp tục pop cho đến khi tìm được valid element

**Tại sao cần check validity?**
- Khi pop element, ta chỉ giảm frequency trong HashMap, không remove khỏi heap
- Heap có thể chứa multiple copies của cùng 1 element với different frequencies

---

## Approach 4: Encode Technique - Single Stack
**Ý tưởng**: Thay vì dùng multiple stacks, encode frequency vào value để dùng 1 stack duy nhất.

**Encoding Formula**: `encoded = (frequency << 16) | value`
- Frequency chiếm 16 bits cao
- Value chiếm 16 bits thấp
- Tự động sort theo frequency (elements có freq cao hơn sẽ có encoded value lớn hơn)

**Decoding**:
- `value = encoded & 0xFFFF`
- `frequency = encoded >> 16`

**Push Operation**:
1. Tăng frequency: `freq[val]++`
2. Encode và push: `st.push(encode(val, freq[val]))`

**Pop Operation**:
1. Lấy encoded value từ top
2. Decode để lấy value và frequency
3. Giảm frequency
4. **Vấn đề**: Cần update maxFreq bằng cách scan toàn bộ stack

**Nhược điểm**: Pop có thể O(n) vì phải tìm maxFreq mới

---

## Approach 5: Ordered Map (TreeMap)
**Ý tưởng**: Dùng `map` (Red-Black Tree) thay vì `unordered_map` để tự động sort buckets theo frequency.

**Cấu trúc dữ liệu**:
- `freq`: map<int, int> - tự động sort theo value
- `buckets`: map<int, stack<int>> - tự động sort theo frequency

**Push Operation**: Tương tự Approach 1

**Pop Operation**:
1. Lấy bucket có frequency cao nhất: `buckets.rbegin()` (reverse iterator)
2. Pop element từ bucket đó
3. Nếu bucket rỗng, tự động remove khỏi map

**Ưu điểm**: Không cần track maxFreq manually, map tự động maintain order

# Complexity
- Time complexity:
  - **Approach 1 (Frequency Buckets)**: $$O(1)$$ push, $$O(1)$$ pop
    - Push: chỉ cần access HashMap và push vào stack
    - Pop: direct access bucket có maxFreq
  - **Approach 2 (Naive)**: $$O(1)$$ push, $$O(n)$$ pop
    - Push: append vào vector
    - Pop: scan toàn bộ n elements
  - **Approach 3 (Priority Queue)**: $$O(\log n)$$ push, $$O(\log n)$$ pop
    - Heap operations có complexity log n
    - Worst case: pop nhiều stale entries
  - **Approach 4 (Encode)**: $$O(1)$$ push, $$O(n)$$ pop (worst case)
    - Push: encode và push vào stack
    - Pop: có thể phải scan stack để tìm maxFreq mới
  - **Approach 5 (TreeMap)**: $$O(\log k)$$ push, $$O(\log k)$$ pop (k = unique frequencies)
    - Map operations có complexity log k
    - k thường << n nên tốt hơn heap

- Space complexity: $$O(n)$$ for all approaches
  - Tất cả đều cần lưu n elements, chỉ khác cách organize

# Code
```cpp []
// Approach 1: Frequency Buckets (Optimal)
class FreqStack {
private:
    unordered_map<int, int> freq;
    unordered_map<int, stack<int>> buckets;
    int maxFreq;
    
public:
    FreqStack() : maxFreq(0) {}
    
    void push(int val) {
        freq[val]++;
        buckets[freq[val]].push(val);
        maxFreq = max(maxFreq, freq[val]);
    }
    
    int pop() {
        int val = buckets[maxFreq].top();
        buckets[maxFreq].pop();
        
        freq[val]--;
        if (buckets[maxFreq].empty()) {
            maxFreq--;
        }
        
        return val;
    }
};
```

**Other Solutions:**
- `solution_naive.cpp`: Naive O(n) approach
- `solution_heap.cpp`: Priority queue approach  
- `solution_encode.cpp`: Single stack with encoding
- `solution_treemap.cpp`: Ordered map approach

# Application in realworld

## 1. LRU/LFU Cache Implementation
**Scenario**: Web browser cache với eviction policy
```cpp
// Khi cache đầy, evict element có frequency thấp nhất
// Nếu tie, evict element được access gần nhất (LRU)
class LFUCache {
    FreqStack freqStack;
    unordered_map<int, int> cache;
    
    void evict() {
        int leastFreqKey = freqStack.pop();
        cache.erase(leastFreqKey);
    }
};
```

## 2. Hot Data Detection in Database
**Scenario**: Identify frequently accessed data for optimization
```cpp
class HotDataDetector {
    FreqStack accessLog;
    
    void recordAccess(int dataId) {
        accessLog.push(dataId);
    }
    
    int getMostAccessedData() {
        return accessLog.pop(); // Most frequent + recent
    }
};
```

## 3. Load Balancer - Server Selection
**Scenario**: Route requests to least frequently used servers
```cpp
class LoadBalancer {
    FreqStack serverUsage;
    
    void routeRequest(int serverId) {
        serverUsage.push(serverId);
        // Process request on serverId
    }
    
    int getLeastUsedServer() {
        return serverUsage.pop(); // Least used server
    }
};
```

## 4. Music Streaming - Recommendation System
**Scenario**: Track most played songs for personalized recommendations
```cpp
class MusicRecommendation {
    FreqStack playHistory;
    
    void playSong(int songId) {
        playHistory.push(songId);
    }
    
    vector<int> getTopSongs(int k) {
        vector<int> topSongs;
        for (int i = 0; i < k; i++) {
            topSongs.push_back(playHistory.pop());
        }
        return topSongs; // Most played + recent songs
    }
};
```

## 5. Error Monitoring System
**Scenario**: Track most frequent errors for debugging priority
```cpp
class ErrorMonitor {
    FreqStack errorLog;
    
    void logError(int errorCode) {
        errorLog.push(errorCode);
    }
    
    int getCriticalError() {
        return errorLog.pop(); // Most frequent error
    }
};
```

**Tại sao FreqStack phù hợp?**
- Cần track frequency (số lần xuất hiện)
- Tie-breaking theo thời gian (recent access wins)
- O(1) operations cho real-time systems

# Related problems
- 146. LRU Cache
- 460. LFU Cache  
- 155. Min Stack
- 716. Max Stack
- 1381. Design a Stack With Increment Operation

# Detailed Implementation Analysis

## Approach 1 - Step by Step Walkthrough
**Example**: Push [5,7,5,7,4,5] then Pop 6 times

### Push Operations:
```
Push 5: freq[5]=1, buckets[1]=[5], maxFreq=1
Push 7: freq[7]=1, buckets[1]=[5,7], maxFreq=1  
Push 5: freq[5]=2, buckets[2]=[5], maxFreq=2
Push 7: freq[7]=2, buckets[2]=[5,7], maxFreq=2
Push 4: freq[4]=1, buckets[1]=[5,7,4], maxFreq=2
Push 5: freq[5]=3, buckets[3]=[5], maxFreq=3
```

**Final State**:
- `buckets[1] = [5,7,4]` (bottom to top)
- `buckets[2] = [5,7]` (bottom to top)  
- `buckets[3] = [5]`
- `maxFreq = 3`

### Pop Operations:
```
Pop 1: maxFreq=3, buckets[3].top()=5, freq[5]=2, buckets[3] empty → maxFreq=2
Pop 2: maxFreq=2, buckets[2].top()=7, freq[7]=1, buckets[2]=[5]
Pop 3: maxFreq=2, buckets[2].top()=5, freq[5]=1, buckets[2] empty → maxFreq=1  
Pop 4: maxFreq=1, buckets[1].top()=4, freq[4]=0, buckets[1]=[5,7]
Pop 5: maxFreq=1, buckets[1].top()=7, freq[7]=0, buckets[1]=[5]
Pop 6: maxFreq=1, buckets[1].top()=5, freq[5]=0, buckets[1] empty → maxFreq=0
```

**Result**: `[5,7,5,4,7,5]` ✅

---

## Approach 3 - Priority Queue Deep Dive
**Tại sao cần check validity?**

### Example với stale entries:
```
Push 5: pq = [{5,1,0}], freq[5]=1
Push 5: pq = [{5,2,1}, {5,1,0}], freq[5]=2
Pop:    pq.top() = {5,2,1}, freq[5]=1 → valid, return 5
        pq = [{5,1,0}], freq[5]=1
Pop:    pq.top() = {5,1,0}, freq[5]=1 → valid, return 5
```

**Nếu không check validity**:
- Sau pop đầu tiên, pq vẫn có `{5,1,0}` 
- Nhưng freq[5] đã giảm xuống 0
- Pop lần 2 sẽ return 5 với frequency sai!

---

## Approach 4 - Encode Technique Explained
**Encoding Logic**:
```cpp
// Encode: (frequency << 16) | value
int encode(int val, int freq) {
    return (freq << 16) | (val & 0xFFFF);
}

// Examples:
// encode(5, 1) = (1 << 16) | 5 = 65541
// encode(5, 2) = (2 << 16) | 5 = 131077  
// encode(5, 3) = (3 << 16) | 5 = 196613
```

**Tại sao encode hoạt động?**
- Elements có frequency cao hơn sẽ có encoded value lớn hơn
- Stack tự động maintain order: frequency cao hơn ở trên top
- Chỉ cần 1 stack thay vì map of stacks

**Vấn đề với approach này**: 
- Khi pop element có maxFreq, cần scan toàn bộ stack để tìm maxFreq mới
- Worst case: O(n) cho mỗi pop operation

---

## So sánh 5 approaches:

| Approach | Push | Pop | Space | Pros | Cons |
|----------|------|-----|--------|------|------|
| Frequency Buckets | O(1) | O(1) | O(n) | Optimal, intuitive | Nhiều buckets |
| Naive | O(1) | O(n) | O(n) | Simple code | Slow pop |
| Priority Queue | O(log n) | O(log n) | O(n) | Standard approach | Stale entries |
| Encode | O(1) | O(n) | O(n) | Single stack | Complex logic |
| TreeMap | O(log k) | O(log k) | O(n) | Auto-sorted | Overhead of tree |

**Kết luận**: Approach 1 (Frequency Buckets) là optimal nhất với O(1) cho cả push và pop.
