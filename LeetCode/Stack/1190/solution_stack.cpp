#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Approach 1: Stack-based Solution (Corrected)
class Solution {
public:
    string reverseParentheses(string s) {
        vector<string> stack;
        string current;
        
        for (char c : s) {
            if (c == '(') {
                // Start new nesting level
                stack.push_back(current);
                current = "";
            } else if (c == ')') {
                // End current level, reverse and combine
                reverse(current.begin(), current.end());
                current = stack.back() + current;
                stack.pop_back();
            } else {
                // Regular character
                current += c;
            }
        }
        
        return current;
    }
};

int main() {
    cout << "Approach 1: Stack-based Solution (Corrected)" << endl;
    cout << "Time: O(n²), Space: O(n)" << endl << endl;
    
    Solution sol;
    
    vector<string> testCases = {
        "(abcd)",
        "(u(love)i)",
        "(ed(et(oc))el)",
        "abcd",
        "",
        "()",
        "((a))",
        "(a(bc)d)",
        "(a(b(c)d)e)",
        "(a)b(c)d",
        "((ab)c(de))",
        "(a(b(c(d)e)f)g)",
        "(((a)))",
        "(ab(cd)ef)"
    };
    
    vector<string> expected = {
        "dcba",
        "iloveu",
        "leetcode",
        "abcd",
        "",
        "",
        "a",
        "dbca",
        "ebcda",
        "abcd",
        "decab",
        "gbedcfa",
        "a",
        "fecdba"
    };
    
    cout << "Testing Reverse Substrings Between Each Pair of Parentheses:" << endl;
    cout << "============================================================" << endl;
    
    for (int i = 0; i < testCases.size(); i++) {
        string input = testCases[i];
        string result = sol.reverseParentheses(input);
        
        cout << "Test Case " << i + 1 << ":" << endl;
        cout << "Input:    \"" << input << "\"" << endl;
        cout << "Output:   \"" << result << "\"" << endl;
        cout << "Expected: \"" << expected[i] << "\"" << endl;
        cout << "Status:   " << (result == expected[i] ? "PASS" : "FAIL") << endl;
        
        // Show step-by-step trace for complex cases
        if (input.length() > 0 && (input.find('(') != string::npos)) {
            cout << "Trace:" << endl;
            vector<string> trace_stack;
            string trace_current;
            
            for (int j = 0; j < input.length(); j++) {
                char c = input[j];
                cout << "  Step " << j + 1 << ": '" << c << "' -> ";
                
                if (c == '(') {
                    trace_stack.push_back(trace_current);
                    trace_current = "";
                    cout << "Push \"" << trace_stack.back() << "\", reset current";
                } else if (c == ')') {
                    reverse(trace_current.begin(), trace_current.end());
                    cout << "Reverse \"" << trace_current << "\", combine with \"" << trace_stack.back() << "\"";
                    trace_current = trace_stack.back() + trace_current;
                    trace_stack.pop_back();
                    cout << " -> \"" << trace_current << "\"";
                } else {
                    trace_current += c;
                    cout << "Add '" << c << "' -> \"" << trace_current << "\"";
                }
                cout << endl;
            }
        }
        
        cout << "-----------------------------------------" << endl;
    }
    
    return 0;
}
