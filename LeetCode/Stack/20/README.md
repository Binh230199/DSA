# 20. Valid Parentheses

## Intuition
The problem asks us to validate if brackets are properly matched and nested. This is a classic stack problem because we need to track opening brackets and match them with their corresponding closing brackets in the correct order (LIFO - Last In, First Out).

## Approach

### Approach 1: Stack with Helper Function (Your Solution)
- Use a stack to store opening brackets
- For each character, check if it forms a valid pair with the top of stack
- If valid pair found, pop from stack; otherwise push to stack
- String is valid if stack is empty at the end

### Approach 2: Traditional Stack Approach
- Push opening brackets onto stack
- For closing brackets, check if stack is empty or top doesn't match
- Pop matching opening bracket from stack
- String is valid if stack is empty at the end

### Approach 3: HashMap/Map Based Approach
- Use a map to store bracket pairs for cleaner code
- Similar logic to approach 2 but with map lookup
- More scalable for different bracket types

### Approach 4: Counter-based Approach (Limited)
- Track count of each bracket type
- Only works for simple cases without proper nesting validation
- Included for educational purposes to show its limitations

## Complexity

### Approach 1: Stack with Helper Function
- Time complexity: $$O(n)$$ - Single pass through string
- Space complexity: $$O(n)$$ - Stack can store up to n/2 opening brackets

### Approach 2: Traditional Stack
- Time complexity: $$O(n)$$ - Single pass through string
- Space complexity: $$O(n)$$ - Stack can store up to n/2 opening brackets

### Approach 3: HashMap Based
- Time complexity: $$O(n)$$ - Single pass through string
- Space complexity: $$O(n)$$ - Stack + constant space for map

### Approach 4: Counter Based
- Time complexity: $$O(n)$$ - Single pass through string
- Space complexity: $$O(1)$$ - Only counters used
- **Note**: This approach is flawed for proper nesting validation

## Code

### Approach 1: Stack with Helper Function (Your Solution)
```cpp
class Solution {
    bool isPairs(char top, char c) {
        if (top == '(' && c == ')') {
            return true;
        }
        if (top == '[' && c == ']') {
            return true;
        }
        if (top == '{' && c == '}') {
            return true;
        }
        return false;
    }
public:
    bool isValid(string s) {
        stack<char> st;
        
        for (const auto& c : s) {
            if (!st.empty() && isPairs(st.top(), c)) {
                st.pop();
            } else {
                st.push(c);
            }
        }
        
        return st.empty();
    }
};
```

### Approach 2: Traditional Stack
```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                st.push(c);
            } else {
                if (st.empty()) return false;
                
                char top = st.top();
                st.pop();
                
                if ((c == ')' && top != '(') ||
                    (c == ']' && top != '[') ||
                    (c == '}' && top != '{')) {
                    return false;
                }
            }
        }
        
        return st.empty();
    }
};
```

### Approach 3: HashMap Based
```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        unordered_map<char, char> pairs = {
            {')', '('},
            {']', '['},
            {'}', '{'}
        };
        
        for (char c : s) {
            if (pairs.find(c) != pairs.end()) { // closing bracket
                if (st.empty() || st.top() != pairs[c]) {
                    return false;
                }
                st.pop();
            } else { // opening bracket
                st.push(c);
            }
        }
        
        return st.empty();
    }
};
```

### Approach 4: Counter Based (Educational - Shows Limitations)
```cpp
class Solution {
public:
    bool isValid(string s) {
        int round = 0, square = 0, curly = 0;
        
        for (char c : s) {
            if (c == '(') round++;
            else if (c == ')') {
                round--;
                if (round < 0) return false;
            }
            else if (c == '[') square++;
            else if (c == ']') {
                square--;
                if (square < 0) return false;
            }
            else if (c == '{') curly++;
            else if (c == '}') {
                curly--;
                if (curly < 0) return false;
            }
        }
        
        return round == 0 && square == 0 && curly == 0;
    }
};
```

## Application in Real World

1. **Compiler Design**: Syntax validation for programming languages
2. **Text Editors**: Bracket matching and highlighting in IDEs
3. **Mathematical Expression Parsing**: Validating mathematical formulas
4. **HTML/XML Validation**: Ensuring proper tag nesting
5. **Configuration File Parsing**: JSON, YAML validation
6. **Code Analysis Tools**: Static analysis for code correctness
7. **Template Engines**: Validating template syntax
8. **Database Query Parsing**: SQL statement validation

## Related Problems

1. **22. Generate Parentheses**: Generate all valid parentheses combinations
2. **32. Longest Valid Parentheses**: Find longest valid parentheses substring
3. **301. Remove Invalid Parentheses**: Remove minimum parentheses to make valid
4. **678. Valid Parenthesis String**: Valid parentheses with wildcards
5. **921. Minimum Add to Make Parentheses Valid**: Minimum additions for validity
6. **1111. Maximum Nesting Depth of Two Valid Parentheses Strings**: Depth balancing
7. **1541. Minimum Insertions to Balance a Parentheses String**: Different bracket rules
8. **1249. Minimum Remove to Make Valid Parentheses**: Remove to make valid
