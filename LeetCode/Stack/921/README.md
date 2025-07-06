# 921. Minimum Add to Make Parentheses Valid

## Intuition
This problem asks us to find the minimum number of parentheses we need to add to make a string valid. The key insight is that we need to count unmatched opening and closing parentheses. Any unmatched `(` needs a corresponding `)`, and any unmatched `)` needs a corresponding `(`.

## Approach

## Approach

### Approach 1: Stack-based Solution (Your Solution)
- Use a stack to track unmatched parentheses
- When we see `(`, push it onto stack
- When we see `)`, check if we can match it with a `(` from stack
- If match found, pop from stack; otherwise, push the unmatched `)`
- Final stack size gives us the number of unmatched parentheses
- **Advantage**: Very intuitive and clear logic
- **Disadvantage**: Uses O(n) extra space

### Approach 2: Counter-based Solution (Space Optimized)
- Use two counters: `open` for unmatched `(` and `close` for unmatched `)`
- When we see `(`, increment open counter
- When we see `)`, try to match with open; if no open available, increment close counter
- Return sum of both counters
- **Advantage**: O(1) space complexity
- **Disadvantage**: Slightly less intuitive than stack approach

### Approach 3: Two-Pass Solution
- Use a boolean array to mark matched parentheses
- First pass: For each `)`, find the rightmost unmatched `(` and mark both as matched
- Second pass: Count all unmarked characters
- Return count of unmatched parentheses
- **Advantage**: Explicit tracking of what's matched vs unmatched
- **Disadvantage**: O(n²) time complexity due to nested loop

## Complexity

### Approach 1: Stack-based Solution
- Time complexity: $$O(n)$$ - Single pass through string
- Space complexity: $$O(n)$$ - Stack can store up to n characters

### Approach 2: Counter-based Solution
- Time complexity: $$O(n)$$ - Single pass through string
- Space complexity: $$O(1)$$ - Only counters used

### Approach 3: Two-Pass Solution
- Time complexity: $$O(n^2)$$ - Nested loop for finding matches
- Space complexity: $$O(n)$$ - Boolean array for tracking matches

## Code

### Approach 1: Stack-based Solution (Your Solution)
```cpp
class Solution {
public:
    int minAddToMakeValid(string s) {
        stack<char> st;
        
        for (const auto& c : s) {
            if (!st.empty() && (st.top() == '(' && c == ')')) {
                st.pop(); // Match found
            } else {
                st.push(c); // Unmatched
            }
        }
        
        return st.size();
    }
};
```

### Approach 2: Counter-based Solution
```cpp
class Solution {
public:
    int minAddToMakeValid(string s) {
        int open = 0, close = 0;
        
        for (char c : s) {
            if (c == '(') {
                open++;
            } else {
                if (open > 0) {
                    open--; // Match found
                } else {
                    close++; // Unmatched ')'
                }
            }
        }
        
        return open + close;
    }
};
```

### Approach 3: Two-Pass Solution
```cpp
class Solution {
public:
    int minAddToMakeValid(string s) {
        int n = s.length();
        vector<bool> matched(n, false);
        
        // First pass: match ')' with '('
        int openCount = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                openCount++;
            } else if (s[i] == ')' && openCount > 0) {
                // Find the rightmost unmatched '('
                for (int j = i - 1; j >= 0; j--) {
                    if (s[j] == '(' && !matched[j]) {
                        matched[j] = true;
                        matched[i] = true;
                        openCount--;
                        break;
                    }
                }
            }
        }
        
        // Count unmatched parentheses
        int unmatched = 0;
        for (int i = 0; i < n; i++) {
            if (!matched[i]) {
                unmatched++;
            }
        }
        
        return unmatched;
    }
};
```

## Application in Real World

1. **Text Editors**: Auto-completion of brackets in IDEs
2. **Compiler Design**: Syntax error detection and recovery
3. **Code Analysis**: Static analysis tools for bracket matching
4. **Mathematical Software**: Validating mathematical expressions
5. **Data Validation**: Checking format correctness in user input
6. **Template Engines**: Validating template syntax with nested structures
7. **Configuration Files**: JSON/XML validation and auto-correction
8. **Network Protocols**: Packet validation with nested headers

## Related Problems

1. **20. Valid Parentheses**: Check if parentheses string is valid
2. **22. Generate Parentheses**: Generate all valid parentheses combinations
3. **32. Longest Valid Parentheses**: Find longest valid parentheses substring
4. **1249. Minimum Remove to Make Valid Parentheses**: Remove characters to make valid
5. **678. Valid Parenthesis String**: Valid parentheses with wildcards
6. **856. Score of Parentheses**: Calculate score of parentheses string
7. **1021. Remove Outermost Parentheses**: Remove outer parentheses
8. **1111. Maximum Nesting Depth of Two Valid Parentheses Strings**: Split parentheses
9. **1541. Minimum Insertions to Balance a Parentheses String**: Different bracket rules
10. **301. Remove Invalid Parentheses**: Remove minimum parentheses to make valid
