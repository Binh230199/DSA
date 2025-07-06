#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Approach 2: Counter-based Solution (Optimized)
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

int main() {
    cout << "Approach 2: Counter-based Solution (Optimized)" << endl;
    cout << "Time: O(n), Space: O(1)" << endl << endl;
    
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
