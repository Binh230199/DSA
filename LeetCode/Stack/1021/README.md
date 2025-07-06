# 1021. Remove Outermost Parentheses

## Intuition
The problem asks us to remove the outermost parentheses of primitive valid parentheses strings. A primitive string is one that cannot be decomposed into two smaller valid parentheses strings. The key insight is to track the nesting depth and only include characters that are not at the outermost level (depth 0 to 1).

## Approach

### Approach 1: Stack-based Solution (Your Solution)
- Use a stack to track parentheses and their nesting levels
- Skip the outermost opening parenthesis (when stack is empty)
- Skip the outermost closing parenthesis (when stack size becomes 1 after popping)
- Add all inner parentheses to the result

### Approach 2: Counter-based Solution (Optimized)
- Use a counter to track the depth of nesting
- Only add parentheses to result when depth > 1 (not outermost)
- Increment counter for '(' and decrement for ')'
- More space-efficient than stack approach

### Approach 3: Two-pointer Approach (Alternative)
- Find primitive strings by tracking opening and closing parentheses
- Extract the inner part of each primitive string
- Concatenate all inner parts

### Approach 4: String Building with Depth Tracking
- Similar to counter approach but with explicit depth tracking
- Build result string character by character
- Clear logic for understanding the depth concept

## Complexity

### Approach 1: Stack-based Solution
- Time complexity: $$O(n)$$ - Single pass through string
- Space complexity: $$O(n)$$ - Stack can store up to n/2 opening parentheses

### Approach 2: Counter-based Solution
- Time complexity: $$O(n)$$ - Single pass through string
- Space complexity: $$O(1)$$ - Only counter and result string

### Approach 3: Two-pointer Approach
- Time complexity: $$O(n)$$ - Single pass through string
- Space complexity: $$O(1)$$ - Only pointers and result string

### Approach 4: String Building with Depth
- Time complexity: $$O(n)$$ - Single pass through string
- Space complexity: $$O(1)$$ - Only depth counter and result string

## Code

### Approach 1: Stack-based Solution (Your Solution)
```cpp
class Solution {
public:
    string removeOuterParentheses(string s) {
        if (s.size() == 1) return "";
        vector<char> st; // Stack to process parenthesis order
        string ret; // Return string

        for (int i = 0; i < s.size(); ++i) {
            // If stack is empty => add "(" to stack
            if (st.empty()) {
                st.push_back(s[i]);
            }
            // If s[i] == the tos ('(' && '( or ')' && ')') => add to stack
            else if (st[st.size() - 1] == s[i]) {
                st.push_back(s[i]);
                ret.push_back(s[i]);
            }
            // If s[i] != tos => remove "()" from stack
            else if (st[st.size() - 1] != s[i]) {
                st.pop_back();
                // if stack size >= 1, it means not outermost closing
                if (st.size() >= 1) {
                    ret.push_back(s[i]);
                }
            }
        }

        return ret;
    }
};
```

### Approach 2: Counter-based Solution (Optimized)
```cpp
class Solution {
public:
    string removeOuterParentheses(string s) {
        string result = "";
        int depth = 0;
        
        for (char c : s) {
            if (c == '(') {
                if (depth > 0) {
                    result += c;
                }
                depth++;
            } else { // c == ')'
                depth--;
                if (depth > 0) {
                    result += c;
                }
            }
        }
        
        return result;
    }
};
```

### Approach 3: Two-pointer Approach
```cpp
class Solution {
public:
    string removeOuterParentheses(string s) {
        string result = "";
        int start = 0;
        int count = 0;
        
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                count++;
            } else {
                count--;
            }
            
            // Found a complete primitive string
            if (count == 0) {
                // Add inner part (exclude first and last characters)
                if (i > start + 1) {
                    result += s.substr(start + 1, i - start - 1);
                }
                start = i + 1;
            }
        }
        
        return result;
    }
};
```

### Approach 4: String Building with Depth Tracking
```cpp
class Solution {
public:
    string removeOuterParentheses(string s) {
        string result = "";
        int openCount = 0;
        
        for (char c : s) {
            if (c == '(' && openCount++ > 0) {
                result += c;
            }
            if (c == ')' && openCount-- > 1) {
                result += c;
            }
        }
        
        return result;
    }
};
```

## Application in Real World

1. **Expression Parsing**: Removing redundant parentheses in mathematical expressions
2. **Code Formatters**: Cleaning up unnecessary parentheses in programming languages
3. **Template Engines**: Processing nested template structures
4. **XML/HTML Processing**: Removing outer tags while preserving inner content
5. **Configuration File Processing**: Simplifying nested configuration structures
6. **Compiler Optimization**: Removing unnecessary grouping in abstract syntax trees
7. **Query Optimization**: Simplifying database query conditions
8. **Text Processing**: Cleaning up nested formatting in markup languages

## Related Problems

1. **20. Valid Parentheses**: Basic parentheses validation
2. **22. Generate Parentheses**: Generate all valid parentheses combinations
3. **32. Longest Valid Parentheses**: Find longest valid parentheses substring
4. **301. Remove Invalid Parentheses**: Remove minimum parentheses to make valid
5. **678. Valid Parenthesis String**: Valid parentheses with wildcards
6. **921. Minimum Add to Make Parentheses Valid**: Minimum additions for validity
7. **1111. Maximum Nesting Depth of Two Valid Parentheses Strings**: Depth balancing
8. **1249. Minimum Remove to Make Valid Parentheses**: Remove to make valid
9. **1541. Minimum Insertions to Balance a Parentheses String**: Different bracket rules
