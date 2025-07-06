# Intuition
Vấn đề mô phỏng navigation trong file system. Cần track depth từ main folder để biết số operations cần thiết để quay về. Stack là natural choice vì "../" tương đương với pop operation.

# Approach

## Approach 1: Stack simulation with vector<bool> (Your Solution)
**Ý tưởng**: Sử dụng vector<bool> để simulate stack, chỉ cần track số lượng folders chứ không cần lưu tên.

**Algorithm**:
- "../": Pop từ stack nếu không empty (quay về parent)
- "./": Ignore (stay current folder)  
- "folder/": Push vào stack (enter folder)
- Return: stack.size() (số steps để về main)

**Ưu điểm**: Your solution rất clever - dùng vector<bool> thay vì full stack

---

## Approach 2: Simple counter (Space Optimized)
**Ý tưởng**: Chỉ cần track depth (số levels từ main folder), không cần lưu folder names.

**Algorithm**:
- "../": depth-- nếu depth > 0
- "./": ignore
- "folder/": depth++
- Return: depth

**Ưu điểm**: O(1) space instead of O(n)

---

## Approach 3: Real stack with folder names
**Ý tưởng**: Sử dụng stack<string> thật để lưu folder names (educational purpose).

**Algorithm**: 
- "../": stack.pop() nếu không empty
- "./": ignore
- "folder/": stack.push(folder)
- Return: stack.size()

**Nhược điểm**: Unnecessary memory overhead (lưu tên folder không cần thiết)

# Complexity
- Time complexity: $$O(n)$$ cho tất cả approaches
  - Process mỗi operation đúng 1 lần

- Space complexity:
  - **Approach 1 (Your solution)**: $$O(n)$$ - vector lưu boolean values
  - **Approach 2 (Counter)**: $$O(1)$$ - chỉ cần 1 integer
  - **Approach 3 (Real stack)**: $$O(n)$$ - lưu folder names

# Code
```cpp []
// Approach 1: Stack simulation with vector<bool> (Your solution)
class Solution {
public:
    int minOperations(vector<string>& logs) {
        vector<bool> st;

        for (const auto& l : logs) {
            if (l == "../") {
                if (!st.empty()) {
                    st.pop_back();
                }
            } else if (l != "./") {
                st.push_back(true);
            }
        }

        return st.size();
    }
};

// Approach 2: Simple counter (Optimal)
class Solution {
public:
    int minOperations(vector<string>& logs) {
        int depth = 0;
        
        for (const string& log : logs) {
            if (log == "../") {
                if (depth > 0) {
                    depth--;
                }
            } else if (log != "./") {
                depth++;
            }
        }
        
        return depth;
    }
};
```

# Detailed Implementation Analysis

## Your Solution Analysis:
**Clever insights trong solution của bạn:**

### **1. vector<bool> thay vì vector<string>**
- Không cần lưu folder names
- Chỉ cần track "có folder nào đó" = push true
- Memory efficient hơn so với lưu strings

### **2. Logic conditions**
```cpp
if (l == "../") {
    // Go to parent - pop if possible
    if (!st.empty()) st.pop_back();
} else if (l != "./") {
    // Not stay current - must be enter folder
    st.push_back(true);
}
// "./": implicitly ignored
```

## Step-by-step Walkthrough:

### **Example 1**: `["d1/","d2/","../","d21/","./"]`

```
Operation | Stack State | Depth | Explanation
----------|-------------|-------|-------------
d1/       | [T]         | 1     | Enter d1 folder
d2/       | [T,T]       | 2     | Enter d2 folder  
../       | [T]         | 1     | Back to d1 (pop)
d21/      | [T,T]       | 2     | Enter d21 folder
./        | [T,T]       | 2     | Stay current (ignore)

Final: depth = 2, need 2 operations to go back
```

### **Example 3**: `["d1/","../","../","../"]`

```
Operation | Stack State | Depth | Explanation
----------|-------------|-------|-------------
d1/       | [T]         | 1     | Enter d1 folder
../       | []          | 0     | Back to main
../       | []          | 0     | Already at main (stay)
../       | []          | 0     | Already at main (stay)

Final: depth = 0, already at main folder
```

## So sánh 3 approaches:

| Approach | Time | Space | Memory Usage | Code Simplicity |
|----------|------|--------|--------------|-----------------|
| Your vector<bool> | O(n) | O(n) | Minimal | Clean |
| Counter | O(n) | O(1) | Optimal | Simplest |
| Real stack | O(n) | O(n) | High | Educational |

**Your solution đã rất tốt!** Chỉ có Approach 2 (counter) tối ưu space hơn.

# Application in realworld

## 1. Shell/Terminal Implementation
```cpp
class ShellNavigator {
    int currentDepth = 0;
    
    void executeCommand(string command) {
        if (command == "cd ..") {
            if (currentDepth > 0) currentDepth--;
        } else if (command == "cd .") {
            // Stay current
        } else if (command.substr(0, 3) == "cd ") {
            currentDepth++;
        }
    }
    
    int getStepsToRoot() {
        return currentDepth;
    }
};
```

## 2. Web Browser Navigation
```cpp
class BrowserHistory {
    vector<bool> navigationStack;
    
    void navigateToSubpage() {
        navigationStack.push_back(true);
    }
    
    void goBack() {
        if (!navigationStack.empty()) {
            navigationStack.pop_back();
        }
    }
    
    int getDepthFromHome() {
        return navigationStack.size();
    }
};
```

## 3. File Explorer Implementation
```cpp
class FileExplorer {
    int folderDepth = 0;
    
    void changeDirectory(string operation) {
        if (operation == "../") {
            if (folderDepth > 0) folderDepth--;
        } else if (operation != "./") {
            folderDepth++;
        }
    }
    
    bool isAtRoot() {
        return folderDepth == 0;
    }
};
```

## 4. Git Repository Navigation
```cpp
class GitNavigator {
    vector<bool> pathStack;
    
    void enterSubmodule() {
        pathStack.push_back(true);
    }
    
    void exitSubmodule() {
        if (!pathStack.empty()) {
            pathStack.pop_back();
        }
    }
    
    int getDistanceFromRoot() {
        return pathStack.size();
    }
};
```

**Why Stack/Counter approach?**
- **Natural mapping**: Folder hierarchy ~ stack structure
- **Undo mechanism**: "../" ~ pop operation
- **Depth tracking**: Stack size = distance from root
- **Memory efficient**: Only need to track count, not names

# Related problems
- 71. Simplify Path
- 20. Valid Parentheses
- 1047. Remove All Adjacent Duplicates In String
- 946. Validate Stack Sequences
- 844. Backspace String Compare
