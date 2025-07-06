# Intuition
Unix path simplification cần xử lý các trường hợp: current directory (.), parent directory (..), multiple slashes (//), và trailing slashes. Stack là cấu trúc dữ liệu tự nhiên vì ".." có nghĩa là "quay lại directory trước đó" (pop operation).

# Approach

## Approach 1: Stack with stringstream (Recommended)
**Ý tưởng**: Sử dụng `stringstream` để split path theo delimiter '/', sau đó xử lý từng component với stack.

**Algorithm**:
1. Split path bằng `getline(ss, token, '/')`
2. Xử lý từng token:
   - Empty token: Skip (do multiple slashes)
   - ".": Skip (current directory)
   - "..": Pop stack nếu có (parent directory)
   - Khác: Push vào stack (valid directory)
3. Rebuild path từ stack

**Ưu điểm**: Code clean, sử dụng built-in string functions

---

## Approach 2: Stack with manual parsing
**Ý tưởng**: Manually parse path character by character, extract directories và xử lý với stack.

**Algorithm**:
1. Duyệt path với pointer i
2. Skip slashes: `while (path[i] == '/')`
3. Extract directory: `while (path[i] != '/')`
4. Process directory như Approach 1
5. Rebuild path

**Ưu điểm**: Không depend vào stringstream, control tốt hơn

---

## Approach 3: Real stack with reverse building
**Ý tưởng**: Dùng `stack<string>` thật thay vì vector, build result ngược từ stack.

**Algorithm**:
1. Parse và push vào stack như approach 2
2. Build result bằng cách pop từ stack:
   - `result = "/" + stack.top() + result`
3. Return result

**Ưu điểm**: Sử dụng stack đúng nghĩa, minh họa LIFO property

# Complexity
- Time complexity: $$O(n)$$ cho tất cả approaches
  - Mỗi character được process đúng 1 lần
  - Building result cũng O(n)

- Space complexity: $$O(n)$$
  - Stack/vector lưu tối đa n/2 directories (worst case)
  - Result string cũng O(n)

# Code
```cpp []
// Approach 1: Stack with stringstream (Recommended)
class Solution {
public:
    string simplifyPath(string path) {
        vector<string> stack;
        stringstream ss(path);
        string token;
        
        while (getline(ss, token, '/')) {
            if (token.empty() || token == ".") continue;
            
            if (token == "..") {
                if (!stack.empty()) {
                    stack.pop_back();
                }
            } else {
                stack.push_back(token);
            }
        }
        
        string result = "/";
        for (int i = 0; i < stack.size(); i++) {
            result += stack[i];
            if (i < stack.size() - 1) {
                result += "/";
            }
        }
        
        return result;
    }
};
```

# Detailed Implementation Analysis

## Edge Cases và Xử lý:

### **1. Multiple consecutive slashes**
```
Input: "/home//foo/"
Process: ["home", "foo"]
Output: "/home/foo"
```

### **2. Parent directory từ root**
```
Input: "/../"
Process: [] (stack empty, không thể pop)
Output: "/"
```

### **3. Dots không phải . hoặc ..**
```
Input: "/.../a/../b"
Process: ["...", "b"] ("..." là valid directory name)
Output: "/.../b"
```

### **4. Trailing slashes**
```
Input: "/home/"
Process: ["home"]
Output: "/home" (remove trailing slash)
```

## Step-by-step Walkthrough:

### **Example**: `/home/user/Documents/../Pictures`

```
Tokens: ["home", "user", "Documents", "..", "Pictures"]

Step 1: token="home" -> stack=["home"]
Step 2: token="user" -> stack=["home", "user"]  
Step 3: token="Documents" -> stack=["home", "user", "Documents"]
Step 4: token=".." -> pop -> stack=["home", "user"]
Step 5: token="Pictures" -> stack=["home", "user", "Pictures"]

Result: "/home/user/Pictures"
```

## So sánh 3 approaches:

| Approach | Parsing Method | Stack Type | Code Complexity | Performance |
|----------|----------------|------------|-----------------|-------------|
| stringstream | getline() | vector<string> | Simple | Fast |
| Manual | Character-by-character | vector<string> | Medium | Fast |
| Real Stack | Character-by-character | stack<string> | Medium | Slightly slower |

**Recommendation**: Approach 1 (stringstream) - cleanest code, good performance

# Application in realworld

## 1. File System Navigation
```cpp
class FileSystemNavigator {
    string currentPath = "/";
    
    void navigateTo(string path) {
        if (path[0] == '/') {
            // Absolute path
            currentPath = simplifyPath(path);
        } else {
            // Relative path
            currentPath = simplifyPath(currentPath + "/" + path);
        }
    }
    
    string getCurrentPath() {
        return currentPath;
    }
};
```

## 2. URL Path Normalization
```cpp
class URLNormalizer {
    string normalizePath(string url) {
        // Extract path part from URL
        size_t pos = url.find("://");
        if (pos != string::npos) {
            pos = url.find("/", pos + 3);
            if (pos != string::npos) {
                string domain = url.substr(0, pos);
                string path = url.substr(pos);
                return domain + simplifyPath(path);
            }
        }
        return url;
    }
};
```

## 3. Build System Path Resolution
```cpp
class BuildPathResolver {
    string resolveIncludePath(string basePath, string includePath) {
        string fullPath = basePath + "/" + includePath;
        return simplifyPath(fullPath);
    }
    
    bool isValidPath(string path) {
        string simplified = simplifyPath(path);
        return !simplified.empty() && simplified[0] == '/';
    }
};
```

## 4. Version Control System
```cpp
class VCSPathNormalizer {
    string normalizeRepoPath(string path) {
        // Remove .git references and normalize
        string normalized = simplifyPath(path);
        
        // Additional VCS-specific logic
        if (normalized.find("/.git/") != string::npos) {
            // Handle .git directory references
        }
        
        return normalized;
    }
};
```

**Tại sao Stack phù hợp?**
- **Natural fit**: ".." operation ~ stack pop
- **LIFO property**: Parent directory là directory được access gần nhất
- **Undo mechanism**: Pop để quay lại previous state
- **Memory efficient**: Chỉ lưu current path components

# Related problems
- 20. Valid Parentheses
- 1047. Remove All Adjacent Duplicates In String
- 394. Decode String
- 150. Evaluate Reverse Polish Notation
- 224. Basic Calculator
