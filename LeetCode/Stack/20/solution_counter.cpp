#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Approach 4: Counter Based Approach (Educational - Shows Limitations)
class Solution {
public:
    bool isValid(string s) {
        int round = 0, square = 0, curly = 0;
        
        for (char c : s) {
            if (c == '(') round++;
            else if (c == ')') {
                round--;
                if (round < 0) return false;
            }
            else if (c == '[') square++;
            else if (c == ']') {
                square--;
                if (square < 0) return false;
            }
            else if (c == '{') curly++;
            else if (c == '}') {
                curly--;
                if (curly < 0) return false;
            }
        }
        
        return round == 0 && square == 0 && curly == 0;
    }
};

int main() {
    cout << "Approach 4: Counter Based Approach (Educational - Shows Limitations)" << endl;
    cout << "Time: O(n), Space: O(1)" << endl;
    cout << "WARNING: This approach has limitations and fails for cases like \"([)]\"" << endl << endl;
    
    Solution sol;
    
    vector<string> testCases = {
        "()",
        "()[]{}", 
        "(]",
        "([])",
        "([)]",     // This will incorrectly return true!
        "{[]}",
        "(((",
        ")))",
        "",
        "()[]{}",
        "([{}])",
        "([)]"      // This will incorrectly return true!
    };
    
    vector<bool> expected = {
        true,   // "()"
        true,   // "()[]{}"
        false,  // "(]"
        true,   // "([])"
        false,  // "([)]" - Counter approach will fail here
        true,   // "{[]}"
        false,  // "((("
        false,  // ")))"
        true,   // ""
        true,   // "()[]{}",
        true,   // "([{}])"
        false   // "([)]" - Counter approach will fail here
    };
    
    cout << "Testing Valid Parentheses (Counter Approach):\n";
    cout << "============================================\n";
    
    for (int i = 0; i < testCases.size(); i++) {
        string s = testCases[i];
        bool result = sol.isValid(s);
        
        cout << "Test Case " << i + 1 << ":\n";
        cout << "Input:    \"" << s << "\"\n";
        cout << "Output:   " << (result ? "true" : "false") << "\n";
        cout << "Expected: " << (expected[i] ? "true" : "false") << "\n";
        cout << "Status:   " << (result == expected[i] ? "PASS" : "FAIL");
        if (result != expected[i]) {
            cout << " <- LIMITATION OF COUNTER APPROACH";
        }
        cout << "\n";
        cout << "-----------------------------------------\n";
    }
    
    cout << "\nNote: Counter approach fails because it doesn't track proper nesting order.\n";
    cout << "For example, \"([)]\" has balanced counts but improper nesting.\n";
    
    return 0;
}
