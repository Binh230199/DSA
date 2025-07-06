#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Approach 3: Recursive Solution (Divide and Conquer)
class Solution {
public:
    int scoreOfParentheses(string s) {
        return helper(s, 0, s.length() - 1);
    }
    
private:
    int helper(const string& s, int left, int right) {
        if (left > right) return 0;
        if (right - left == 1) return 1; // "()"
        
        int balance = 0, score = 0, start = left;
        
        for (int i = left; i <= right; i++) {
            if (s[i] == '(') balance++;
            else balance--;
            
            if (balance == 0) {
                if (start == left && i == right) {
                    // Entire range is wrapped: (A)
                    return 2 * helper(s, left + 1, right - 1);
                } else {
                    // Add score of current balanced part
                    if (i - start == 1) {
                        score += 1; // "()"
                    } else {
                        score += 2 * helper(s, start + 1, i - 1); // "(A)"
                    }
                    start = i + 1;
                }
            }
        }
        
        return score;
    }
};

int main() {
    cout << "Approach 3: Recursive Solution (Divide and Conquer)" << endl;
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
