#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Approach 2: Counter-based Solution (Space Optimized)
class Solution {
public:
    int minAddToMakeValid(string s) {
        int open = 0, close = 0;
        
        for (char c : s) {
            if (c == '(') {
                open++;
            } else { // c == ')'
                if (open > 0) {
                    open--; // Match with previous '('
                } else {
                    close++; // Unmatched ')', need to add '('
                }
            }
        }
        
        // open = unmatched '(' (need to add ')')
        // close = unmatched ')' (need to add '(')
        return open + close;
    }
};

int main() {
    cout << "Approach 2: Counter-based Solution (Space Optimized)" << endl;
    cout << "Time: O(n), Space: O(1)" << endl << endl;
    
    Solution sol;
    
    vector<string> testCases = {
        "())",
        "(((", 
        "()",
        "()())",
        ")())",
        "(((",
        ")))",
        "",
        "(()()",
        "))((",
        "()()()",
        "((()))",
        ")()()("
    };
    
    vector<int> expected = {
        1,    // "())" - need 1 '('
        3,    // "(((" - need 3 ')'
        0,    // "()" - already valid
        1,    // "()())" - need 1 '('
        2,    // ")())" - need 1 '(' and 1 '('
        3,    // "(((" - need 3 ')'
        3,    // ")))" - need 3 '('
        0,    // "" - empty is valid
        2,    // "(()()" - need 1 ')' and 1 ')'
        4,    // "))((" - need 2 '(' and 2 ')'
        0,    // "()()()" - already valid
        0,    // "((()))" - already valid
        2     // ")()()(" - need 1 '(' and 1 ')'
    };
    
    cout << "Testing Minimum Add to Make Parentheses Valid:\n";
    cout << "=============================================\n";
    
    for (int i = 0; i < testCases.size(); i++) {
        string s = testCases[i];
        int result = sol.minAddToMakeValid(s);
        
        cout << "Test Case " << i + 1 << ":\n";
        cout << "Input:    \"" << s << "\"\n";
        cout << "Output:   " << result << "\n";
        cout << "Expected: " << expected[i] << "\n";
        cout << "Status:   " << (result == expected[i] ? "PASS" : "FAIL") << "\n";
        cout << "-----------------------------------------\n";
    }
    
    return 0;
}
