#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

// Approach 2: Two-Pass Solution
class Solution {
public:
    string reverseParentheses(string s) {
        int n = s.length();
        vector<int> pair(n);
        stack<int> st;
        
        // First pass: find matching parentheses
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                st.push(i);
            } else if (s[i] == ')') {
                int j = st.top();
                st.pop();
                pair[i] = j;
                pair[j] = i;
            }
        }
        
        // Second pass: build result with direction tracking
        string result;
        int direction = 1; // 1 for forward, -1 for backward
        
        for (int i = 0; i < n; ) {
            if (s[i] == '(' || s[i] == ')') {
                i = pair[i];
                direction = -direction;
            } else {
                result += s[i];
            }
            i += direction;
        }
        
        return result;
    }
};

int main() {
    cout << "Approach 2: Two-Pass Solution" << endl;
    cout << "Time: O(n), Space: O(n)" << endl << endl;
    
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
        "(a(b(c(d)e)f)g)"
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
        "gbedcfa"
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
        
        // Show parentheses pairing for complex cases
        if (input.length() > 0 && (input.find('(') != string::npos)) {
            cout << "Parentheses pairs:" << endl;
            int n = input.length();
            vector<int> pair(n);
            stack<int> st;
            
            for (int j = 0; j < n; j++) {
                if (input[j] == '(') {
                    st.push(j);
                } else if (input[j] == ')') {
                    int k = st.top();
                    st.pop();
                    pair[j] = k;
                    pair[k] = j;
                    cout << "  '(' at position " << k << " matches ')' at position " << j << endl;
                }
            }
        }
        
        cout << "-----------------------------------------" << endl;
    }
    
    return 0;
}
