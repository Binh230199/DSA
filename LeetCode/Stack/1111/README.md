# 1111. Maximum Nesting Depth of Two Valid Parentheses Strings

## Intuition
This problem asks us to split a valid parentheses string into two disjoint subsequences A and B, such that both A and B are valid parentheses strings, and we want to minimize the maximum nesting depth between A and B.

The key insight is that to minimize the maximum depth, we should **distribute the nesting levels evenly** between the two groups. When we encounter nested parentheses, instead of putting them all in one group (which would create deep nesting), we alternate between groups.

## Approach

### Approach 1: Depth-based Distribution (Counter)
The main idea is to track the current depth and assign parentheses to different groups based on the depth level:

1. **Track current depth**: As we scan through the string, maintain the current nesting depth
2. **Distribute by depth level**: 
   - If current depth is odd → assign to group 0
   - If current depth is even → assign to group 1
3. **Maintain pairing**: Each closing `)` must be assigned to the same group as its corresponding opening `(`

**Step-by-step process:**
- For each `(`: assign to group based on current depth, then increment depth
- For each `)`: decrement depth first, then assign to group based on new depth

### Approach 2: Stack-based Tracking
Use a stack to explicitly track which group each opening parenthesis belongs to:

1. **Stack for group tracking**: Stack stores the group assignment for each unmatched opening parenthesis
2. **Alternating assignment**: Assign opening parentheses to alternate groups based on current stack depth
3. **Matching pairs**: Each closing parenthesis gets the same group as its matching opening parenthesis

### Approach 3: Simple Alternating (Optimized)
Since we want to minimize maximum depth, we can simply alternate between groups based on the current depth:

1. **Depth tracking**: Keep track of current nesting depth
2. **Group assignment**: Use depth % 2 to decide which group (0 or 1)
3. **Pair maintenance**: Ensure matching parentheses are in the same group

## Complexity

### Approach 1: Depth-based Distribution
- Time complexity: $$O(n)$$ - Single pass through the string
- Space complexity: $$O(1)$$ - Only using counters

### Approach 2: Stack-based Tracking
- Time complexity: $$O(n)$$ - Single pass through the string
- Space complexity: $$O(n)$$ - Stack can store up to n/2 elements

### Approach 3: Simple Alternating
- Time complexity: $$O(n)$$ - Single pass through the string
- Space complexity: $$O(1)$$ - Only using counters

## Code

### Approach 1: Depth-based Distribution (Counter)
```cpp
class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> result(seq.length());
        int depth = 0;
        
        for (int i = 0; i < seq.length(); i++) {
            if (seq[i] == '(') {
                // Assign to group based on current depth
                result[i] = depth % 2;
                depth++;
            } else { // seq[i] == ')'
                depth--;
                // Assign to same group as matching opening
                result[i] = depth % 2;
            }
        }
        
        return result;
    }
};
```

### Approach 2: Stack-based Tracking
```cpp
class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> result(seq.length());
        stack<int> groupStack;
        
        for (int i = 0; i < seq.length(); i++) {
            if (seq[i] == '(') {
                // Assign to group based on current stack depth
                int group = groupStack.size() % 2;
                result[i] = group;
                groupStack.push(group);
            } else { // seq[i] == ')'
                // Assign to same group as matching opening
                result[i] = groupStack.top();
                groupStack.pop();
            }
        }
        
        return result;
    }
};
```

### Approach 3: Simple Alternating (Optimized)
```cpp
class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> result(seq.length());
        int depth = 0;
        
        for (int i = 0; i < seq.length(); i++) {
            if (seq[i] == '(') {
                result[i] = depth % 2;
                depth++;
            } else {
                depth--;
                result[i] = depth % 2;
            }
        }
        
        return result;
    }
};
```

## Application in realworld

1. **Expression Parsing**: Distributing nested expressions across multiple processors for parallel evaluation
2. **Code Formatting**: Balancing nested code blocks across different indentation levels
3. **Data Structure Design**: Balancing tree structures to minimize maximum depth
4. **Load Balancing**: Distributing nested tasks across multiple workers to minimize maximum workload

## Related problems

- **20. Valid Parentheses**: Basic parentheses validation
- **22. Generate Parentheses**: Generate all valid parentheses combinations
- **32. Longest Valid Parentheses**: Find longest valid parentheses substring
- **301. Remove Invalid Parentheses**: Remove minimum parentheses to make valid
- **921. Minimum Add to Make Parentheses Valid**: Add minimum parentheses to make valid
- **1190. Reverse Substrings Between Each Pair of Parentheses**: Process nested parentheses structure
