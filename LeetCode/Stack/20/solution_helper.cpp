#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

// Approach 1: Stack with Helper Function (Your Solution)
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

int main() {
    cout << "Approach 1: Stack with Helper Function (Your Solution)" << endl;
    cout << "Time: O(n), Space: O(n)" << endl << endl;
    
    Solution sol;
    
    vector<string> testCases = {
        "()",
        "()[]{}", 
        "(]",
        "([])",
        "([)]",
        "{[]}",
        "(((",
        ")))",
        "",
        "()[]{}",
        "([{}])",
        "([)]"
    };
    
    vector<bool> expected = {
        true,   // "()"
        true,   // "()[]{}"
        false,  // "(]"
        true,   // "([])"
        false,  // "([)]"
        true,   // "{[]}"
        false,  // "((("
        false,  // ")))"
        true,   // ""
        true,   // "()[]{}",
        true,   // "([{}])"
        false   // "([)]"
    };
    
    cout << "Testing Valid Parentheses:\n";
    cout << "=========================\n";
    
    for (int i = 0; i < testCases.size(); i++) {
        string s = testCases[i];
        bool result = sol.isValid(s);
        
        cout << "Test Case " << i + 1 << ":\n";
        cout << "Input:    \"" << s << "\"\n";
        cout << "Output:   " << (result ? "true" : "false") << "\n";
        cout << "Expected: " << (expected[i] ? "true" : "false") << "\n";
        cout << "Status:   " << (result == expected[i] ? "PASS" : "FAIL") << "\n";
        cout << "-----------------------------------------\n";
    }
    
    return 0;
}
