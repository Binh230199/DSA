#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Approach 4: String Parsing (Alternative)
class Solution {
public:
    int scoreOfParentheses(string s) {
        return parseScore(s, 0, s.length() - 1);
    }
    
private:
    int parseScore(const string& s, int start, int end) {
        if (start > end) return 0;
        if (end - start == 1) return 1; // "()"
        
        int depth = 0, score = 0, lastStart = start;
        
        for (int i = start; i <= end; i++) {
            if (s[i] == '(') depth++;
            else depth--;
            
            if (depth == 0) {
                if (lastStart == start && i == end) {
                    // Entire string is wrapped
                    return 2 * parseScore(s, start + 1, end - 1);
                } else {
                    // Add score of current segment
                    if (i - lastStart == 1) {
                        score += 1; // "()"
                    } else {
                        score += 2 * parseScore(s, lastStart + 1, i - 1);
                    }
                    lastStart = i + 1;
                }
            }
        }
        
        return score;
    }
};

int main() {
    cout << "Approach 4: String Parsing (Alternative)" << endl;
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
