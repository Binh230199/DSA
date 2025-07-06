#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Approach 1: Stack-based Solution (Your Solution)
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

int main() {
    cout << "Approach 1: Stack-based Solution (Your Solution)" << endl;
    cout << "Time: O(n), Space: O(n)" << endl << endl;
    
    Solution sol;
    
    vector<string> testCases = {
        "(()())(())",
        "(()())(())(()(()))",
        "()()",
        "()",
        "(()(()))",
        "(())",
        "((()))",
        "()()()",
        "(()(()()))",
        "(((())))"
    };
    
    vector<string> expected = {
        "()()()",
        "()()()()(())",
        "",
        "",
        "()(())",
        "()",
        "(())",
        "",
        "()(()())",
        "((()))"
    };
    
    cout << "Testing Remove Outermost Parentheses:\n";
    cout << "====================================\n";
    
    for (int i = 0; i < testCases.size(); i++) {
        string s = testCases[i];
        string result = sol.removeOuterParentheses(s);
        
        cout << "Test Case " << i + 1 << ":\n";
        cout << "Input:    \"" << s << "\"\n";
        cout << "Output:   \"" << result << "\"\n";
        cout << "Expected: \"" << expected[i] << "\"\n";
        cout << "Status:   " << (result == expected[i] ? "PASS" : "FAIL") << "\n";
        cout << "-----------------------------------------\n";
    }
    
    return 0;
}
