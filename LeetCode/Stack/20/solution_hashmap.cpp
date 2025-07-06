#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

// Approach 3: HashMap Based Approach
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

int main() {
    cout << "Approach 3: HashMap Based Approach" << endl;
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
