#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Approach 3: Two-Pass Solution (Left-to-Right, Right-to-Left)
class Solution {
public:
    int minAddToMakeValid(string s) {
        int n = s.length();
        vector<bool> matched(n, false);
        
        // First pass: Left to Right - match ')' with '('
        int openCount = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                openCount++;
            } else if (s[i] == ')' && openCount > 0) {
                // Find the rightmost unmatched '('
                for (int j = i - 1; j >= 0; j--) {
                    if (s[j] == '(' && !matched[j]) {
                        matched[j] = true;
                        matched[i] = true;
                        openCount--;
                        break;
                    }
                }
            }
        }
        
        // Count unmatched parentheses
        int unmatched = 0;
        for (int i = 0; i < n; i++) {
            if (!matched[i]) {
                unmatched++;
            }
        }
        
        return unmatched;
    }
};

int main() {
    cout << "Approach 3: Two-Pass Solution (Left-to-Right, Right-to-Left)" << endl;
    cout << "Time: O(n²), Space: O(n)" << endl << endl;
    
    Solution sol;
    
    vector<string> testCases = {
        "())",
        "(((",
        "()",
        "())())",
        "((())",
        ")()())",
        "",
        "(()",
        "())",
        "(((((("
    };
    
    vector<int> expected = {1, 3, 0, 4, 2, 4, 0, 1, 1, 6};
    
    for (int i = 0; i < testCases.size(); i++) {
        string s = testCases[i];
        int result = sol.minAddToMakeValid(s);
        cout << "Input: \"" << s << "\"" << endl;
        cout << "Output: " << result << endl;
        cout << "Expected: " << expected[i] << endl;
        cout << "Status: " << (result == expected[i] ? "PASS" : "FAIL") << endl;
        cout << "---" << endl;
    }
    
    return 0;
}
