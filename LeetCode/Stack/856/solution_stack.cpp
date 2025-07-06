#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

// Approach 1: Stack-based Solution (Most Intuitive)
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

int main() {
    cout << "Approach 1: Stack-based Solution (Most Intuitive)" << endl;
    cout << "Time: O(n), Space: O(n)" << endl << endl;
    
    Solution sol;
    
    vector<string> testCases = {
        "()",
        "(())",
        "()()",
        "(()(()))",
        "(((())))",
        "(()())",
        "()(())",
        "((()))",
        "(())()",
        "(()(()()))"
    };
    
    vector<int> expected = {
        1,    // "()"
        2,    // "(())"
        2,    // "()()"
        6,    // "(()(()))"
        8,    // "(((())))"
        4,    // "(()())"
        3,    // "()(())"
        4,    // "((()))"
        3,    // "(())()"
        10    // "(()(()()))"
    };
    
    cout << "Testing Score of Parentheses:\n";
    cout << "============================\n";
    
    for (int i = 0; i < testCases.size(); i++) {
        string s = testCases[i];
        int result = sol.scoreOfParentheses(s);
        
        cout << "Test Case " << i + 1 << ":\n";
        cout << "Input:    \"" << s << "\"\n";
        cout << "Output:   " << result << "\n";
        cout << "Expected: " << expected[i] << "\n";
        cout << "Status:   " << (result == expected[i] ? "PASS" : "FAIL") << "\n";
        cout << "-----------------------------------------\n";
    }
    
    return 0;
}
