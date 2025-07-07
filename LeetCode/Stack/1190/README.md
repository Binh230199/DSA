# 1190. Reverse Substrings Between Each Pair of Parentheses

## Intuition
This problem asks us to reverse substrings within parentheses, starting from the innermost ones. The key insight is that we need to process nested parentheses from inside out, which naturally suggests using a stack-based approach.

When we encounter an opening parenthesis '(', we need to start a new context. When we encounter a closing parenthesis ')', we need to reverse the current substring and merge it with the previous context.

## Approach

### Approach 1: Stack-based Solution (Corrected Version)
The main idea is to use a stack to keep track of different levels of nesting:

1. **Stack of strings**: Each element in the stack represents a different nesting level
2. **Current substring**: Build the current substring character by character
3. **Opening parenthesis**: Push current substring to stack, start new substring
4. **Closing parenthesis**: Reverse current substring, combine with previous level
5. **Regular character**: Add to current substring

**Key operations:**
- `'('`: Push current substring to stack, reset current substring
- `')'`: Reverse current substring, combine with stack top, pop from stack
- `letter`: Add to current substring

### Approach 2: Two-Pass Solution
An alternative approach using two passes:

1. **First pass**: Find all matching parentheses pairs and store their positions
2. **Second pass**: Process the string by reversing substrings based on the stored pairs

### Approach 3: Simulation with Stack
Use a stack to simulate the nesting process:

1. **Character stack**: Store characters and track when to reverse
2. **Marker approach**: Use special markers to indicate reversal points
3. **Build result**: Construct the final string by processing the stack

## Complexity

### Approach 1: Stack-based Solution
- Time complexity: $$O(n^2)$$ - In worst case, we might reverse substrings multiple times
- Space complexity: $$O(n)$$ - Stack can store multiple levels of nesting

### Approach 2: Two-Pass Solution
- Time complexity: $$O(n^2)$$ - Finding pairs and reversing substrings
- Space complexity: $$O(n)$$ - Storage for pair positions

### Approach 3: Simulation with Stack
- Time complexity: $$O(n^2)$$ - Multiple reversals possible
- Space complexity: $$O(n)$$ - Character stack storage

## Code

### Approach 1: Stack-based Solution (Corrected)
```cpp
class Solution {
public:
    string reverseParentheses(string s) {
        vector<string> stack;
        string current;
        
        for (char c : s) {
            if (c == '(') {
                // Start new nesting level
                stack.push_back(current);
                current = "";
            } else if (c == ')') {
                // End current level, reverse and combine
                reverse(current.begin(), current.end());
                current = stack.back() + current;
                stack.pop_back();
            } else {
                // Regular character
                current += c;
            }
        }
        
        return current;
    }
};
```

### Approach 2: Two-Pass Solution
```cpp
class Solution {
public:
    string reverseParentheses(string s) {
        int n = s.length();
        vector<int> pair(n);
        stack<int> st;
        
        // First pass: find matching parentheses
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                st.push(i);
            } else if (s[i] == ')') {
                int j = st.top();
                st.pop();
                pair[i] = j;
                pair[j] = i;
            }
        }
        
        // Second pass: build result
        string result;
        int direction = 1; // 1 for forward, -1 for backward
        
        for (int i = 0; i < n; ) {
            if (s[i] == '(' || s[i] == ')') {
                i = pair[i];
                direction = -direction;
            } else {
                result += s[i];
            }
            i += direction;
        }
        
        return result;
    }
};
```

### Approach 3: Simulation with Stack
```cpp
class Solution {
public:
    string reverseParentheses(string s) {
        stack<string> st;
        string current = "";
        
        for (char c : s) {
            if (c == '(') {
                st.push(current);
                current = "";
            } else if (c == ')') {
                reverse(current.begin(), current.end());
                if (!st.empty()) {
                    current = st.top() + current;
                    st.pop();
                }
            } else {
                current += c;
            }
        }
        
        return current;
    }
};
```

## Application in realworld

1. **Text Processing**: Reversing specific portions of text based on markup or delimiters
2. **Expression Evaluation**: Processing nested expressions with special reversal rules
3. **String Manipulation**: Advanced string processing in text editors or formatters
4. **Parse Tree Construction**: Building parse trees for languages with special reversal semantics
5. **Data Transformation**: Transforming nested data structures with reversal requirements

## Related problems

- **20. Valid Parentheses**: Basic parentheses validation
- **22. Generate Parentheses**: Generate all valid parentheses combinations
- **32. Longest Valid Parentheses**: Find longest valid parentheses substring
- **301. Remove Invalid Parentheses**: Remove minimum parentheses to make valid
- **921. Minimum Add to Make Parentheses Valid**: Add minimum parentheses to make valid
- **1111. Maximum Nesting Depth of Two Valid Parentheses Strings**: Split parentheses to minimize depth
- **1021. Remove Outermost Parentheses**: Remove outer parentheses from valid strings
