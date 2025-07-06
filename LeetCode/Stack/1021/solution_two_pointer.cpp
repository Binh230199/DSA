#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Approach 3: Two-pointer Approach
class Solution {
public:
    string removeOuterParentheses(string s) {
        string result = "";
        int start = 0;
        int count = 0;
        
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                count++;
            } else {
                count--;
            }
            
            // Found a complete primitive string
            if (count == 0) {
                // Add inner part (exclude first and last characters)
                if (i > start + 1) {
                    result += s.substr(start + 1, i - start - 1);
                }
                start = i + 1;
            }
        }
        
        return result;
    }
};

int main() {
    cout << "Approach 3: Two-pointer Approach" << endl;
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
