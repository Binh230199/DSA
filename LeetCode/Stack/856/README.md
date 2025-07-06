# 856. Score of Parentheses

## Intuition
This problem requires us to calculate the score of a balanced parentheses string based on specific rules:
- `()` has score 1
- `AB` has score A + B (concatenation)
- `(A)` has score 2 * A (wrapping)

The key insight is that we need to track scores at different nesting levels and combine them appropriately when closing parentheses.

## Approach

### Approach 1: Stack-based Solution (Most Intuitive)
- Use a stack to store scores at each nesting level
- When encountering `(`, push 0 (start new level)
- When encountering `)`, pop current level score, calculate new score, and add to previous level
- The magic formula: `prev + max(2 * cur, 1)`

### Approach 2: Counter-based Solution (Space Optimized)
- Track depth and only count when we find `()`
- Each `()` at depth d contributes 2^d to the final score
- More space-efficient: O(1) instead of O(n)

### Approach 3: Recursive Solution (Divide and Conquer)
- Split string into balanced parts at depth 0
- Recursively calculate score for each part
- Handle wrapping by multiplying inner score by 2

### Approach 4: String Parsing (Alternative)
- Parse the string to identify primitive units
- Calculate score for each unit and sum them up
- Less efficient but educational

## Complexity

### Approach 1: Stack-based Solution
- Time complexity: $$O(n)$$ - Single pass through string
- Space complexity: $$O(n)$$ - Stack can store up to n/2 levels

### Approach 2: Counter-based Solution
- Time complexity: $$O(n)$$ - Single pass through string
- Space complexity: $$O(1)$$ - Only variables used

### Approach 3: Recursive Solution
- Time complexity: $$O(n)$$ - Each character processed once
- Space complexity: $$O(n)$$ - Recursion stack depth

### Approach 4: String Parsing
- Time complexity: $$O(n)$$ - Single pass through string
- Space complexity: $$O(n)$$ - Substring operations

## Code

### Approach 1: Stack-based Solution
```cpp
class Solution {
public:
    int scoreOfParentheses(string s) {
        stack<int> st;
        st.push(0); // Base score
        
        for (char c : s) {
            if (c == '(') {
                st.push(0); // Start new level
            } else {
                int cur = st.top(); st.pop();
                int prev = st.top(); st.pop();
                st.push(prev + max(2 * cur, 1));
            }
        }
        
        return st.top();
    }
};
```

### Approach 2: Counter-based Solution
```cpp
class Solution {
public:
    int scoreOfParentheses(string s) {
        int result = 0, depth = 0;
        
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                depth++;
            } else {
                depth--;
                if (s[i-1] == '(') { // Found "()"
                    result += 1 << depth; // Add 2^depth
                }
            }
        }
        
        return result;
    }
};
```

### Approach 3: Recursive Solution
```cpp
class Solution {
public:
    int scoreOfParentheses(string s) {
        return helper(s, 0, s.length() - 1);
    }
    
private:
    int helper(const string& s, int left, int right) {
        if (left > right) return 0;
        if (right - left == 1) return 1; // "()"
        
        int balance = 0, last = left;
        for (int i = left; i <= right; i++) {
            if (s[i] == '(') balance++;
            else balance--;
            
            if (balance == 0) {
                if (last == left) {
                    // Wrapped case: (A)
                    return 2 * helper(s, left + 1, right - 1);
                } else {
                    // Split case: AB
                    return helper(s, last, i) + helper(s, i + 1, right);
                }
            }
            if (balance == 0) last = i + 1;
        }
        
        return 0;
    }
};
```

### Approach 4: String Parsing
```cpp
class Solution {
public:
    int scoreOfParentheses(string s) {
        return parseScore(s, 0, s.length() - 1);
    }
    
private:
    int parseScore(const string& s, int start, int end) {
        if (start > end) return 0;
        if (end - start == 1) return 1; // "()"
        
        int depth = 0, score = 0, lastStart = start;
        
        for (int i = start; i <= end; i++) {
            if (s[i] == '(') depth++;
            else depth--;
            
            if (depth == 0) {
                if (lastStart == start && i == end) {
                    // Entire string is wrapped
                    return 2 * parseScore(s, start + 1, end - 1);
                } else {
                    // Add score of current segment
                    if (i - lastStart == 1) {
                        score += 1; // "()"
                    } else {
                        score += 2 * parseScore(s, lastStart + 1, i - 1);
                    }
                    lastStart = i + 1;
                }
            }
        }
        
        return score;
    }
};
```

## Application in Real World

1. **Mathematical Expression Evaluation**: Handling nested parentheses in calculators
2. **Compiler Design**: Parsing nested scopes and calculating precedence
3. **Data Structure Serialization**: Calculating weights for nested structures
4. **Game Development**: Scoring systems with nested bonus multipliers
5. **Financial Modeling**: Calculating compound interest with nested time periods
6. **XML/JSON Processing**: Calculating depth-based scores for nested elements
7. **Code Analysis**: Measuring cyclomatic complexity with nested blocks
8. **Network Protocols**: Calculating header sizes with nested encapsulation

## Related Problems

1. **20. Valid Parentheses**: Basic parentheses validation
2. **22. Generate Parentheses**: Generate all valid parentheses combinations
3. **32. Longest Valid Parentheses**: Find longest valid parentheses substring
4. **678. Valid Parenthesis String**: Valid parentheses with wildcards
5. **1021. Remove Outermost Parentheses**: Remove outer parentheses from primitives
6. **1111. Maximum Nesting Depth of Two Valid Parentheses Strings**: Depth balancing
7. **1190. Reverse Substrings Between Each Pair of Parentheses**: String manipulation with parentheses
8. **1541. Minimum Insertions to Balance a Parentheses String**: Balance parentheses with different rules
9. **394. Decode String**: Nested string decoding with brackets
10. **726. Number of Atoms**: Parse nested chemical formulas
