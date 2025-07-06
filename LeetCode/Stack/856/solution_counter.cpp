#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Approach 2: Counter-based Solution (Space Optimized)
class Solution {
public:
    int scoreOfParentheses(string s) {
        int result = 0, depth = 0;
        
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                depth++;
            } else {
                depth--;
                if (s[i-1] == '(') { // Found "()"
                    result += 1 << depth; // Add 2^depth
                }
            }
        }
        
        return result;
    }
};

int main() {
    cout << "Approach 2: Counter-based Solution (Space Optimized)" << endl;
    cout << "Time: O(n), Space: O(1)" << endl << endl;
    
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
