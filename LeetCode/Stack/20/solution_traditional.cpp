#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

// Approach 2: Traditional Stack Approach
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

int main() {
    cout << "Approach 2: Traditional Stack Approach" << endl;
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
