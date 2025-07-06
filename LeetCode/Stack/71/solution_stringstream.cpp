#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// Approach 1: Stack with stringstream (Your original solution)
class Solution {
public:
    string simplifyPath(string path) {
        vector<string> stack;
        stringstream ss(path);
        string token;
        
        // Split path by '/' delimiter
        while (getline(ss, token, '/')) {
            // Skip empty tokens (caused by multiple consecutive slashes)
            if (token.empty()) continue;
            
            // Handle current directory '.'
            if (token == ".") continue;
            
            // Handle parent directory '..'
            if (token == "..") {
                if (!stack.empty()) {
                    stack.pop_back();
                }
            } else {
                // Valid directory/file name
                stack.push_back(token);
            }
        }
        
        // Build the simplified path
        string result = "/";
        for (int i = 0; i < stack.size(); i++) {
            result += stack[i];
            if (i < stack.size() - 1) {
                result += "/";
            }
        }
        
        return result;
    }
};

int main() {
    cout << "Approach 1: Stack with stringstream" << endl;
    cout << "Time: O(n), Space: O(n)" << endl << endl;
    
    Solution sol;
    
    vector<string> testCases = {
        "/home/",
        "/home//foo/",
        "/home/user/Documents/../Pictures",
        "/../",
        "/.../a/../b/c/../d/./"
    };
    
    vector<string> expected = {
        "/home",
        "/home/foo",
        "/home/user/Pictures",
        "/",
        "/.../b/d"
    };
    
    cout << "Testing Simplify Path Solution:\n";
    cout << "================================\n";
    
    for (int i = 0; i < testCases.size(); i++) {
        string result = sol.simplifyPath(testCases[i]);
        cout << "Input:    \"" << testCases[i] << "\"\n";
        cout << "Output:   \"" << result << "\"\n";
        cout << "Expected: \"" << expected[i] << "\"\n";
        cout << "Status:   " << (result == expected[i] ? "PASS" : "FAIL") << "\n";
        cout << "--------------------------------\n";
    }
    
    return 0;
}
