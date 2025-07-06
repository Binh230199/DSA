#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Approach 4: String Building with Depth Tracking
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

int main() {
    cout << "Approach 4: String Building with Depth Tracking" << endl;
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
