#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

// Approach 1: Stack-based Solution (Your Solution)
class Solution {
public:
    int minAddToMakeValid(string s) {
        stack<char> st;

        for (const auto& c : s) {
            if (!st.empty() && (st.top() == '(' && c == ')')) {
                st.pop(); // Match found
            } else {
                st.push(c); // Unmatched
            }
        }

        return st.size();
    }
};

int main() {
    cout << "Approach 1: Stack-based Solution (Your Solution)" << endl;
    cout << "Time: O(n), Space: O(n)" << endl << endl;
    
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
