#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Approach 2: Stack with manual parsing
class Solution {
public:
    string simplifyPath(string path) {
        vector<string> stack;
        int i = 0;
        int n = path.length();
        
        while (i < n) {
            // Skip slashes
            while (i < n && path[i] == '/') {
                i++;
            }
            
            // Extract directory name
            string dir = "";
            while (i < n && path[i] != '/') {
                dir += path[i];
                i++;
            }
            
            // Process directory
            if (dir == "" || dir == ".") {
                continue;  // Skip empty or current directory
            } else if (dir == "..") {
                if (!stack.empty()) {
                    stack.pop_back();
                }
            } else {
                stack.push_back(dir);
            }
        }
        
        // Build result
        string result = "/";
        for (int j = 0; j < stack.size(); j++) {
            result += stack[j];
            if (j < stack.size() - 1) {
                result += "/";
            }
        }
        
        return result;
    }
};

int main() {
    cout << "Approach 2: Stack with manual parsing" << endl;
    cout << "Time: O(n), Space: O(n)" << endl << endl;
    
    Solution sol;
    
    vector<string> testCases = {
        "/home/",
        "/home//foo/",
        "/home/user/Documents/../Pictures",
        "/../",
        "/.../a/../b/c/../d/./"
    };
    
    cout << "Testing Manual Parsing Solution:\n";
    cout << "=================================\n";
    
    for (const string& test : testCases) {
        string result = sol.simplifyPath(test);
        cout << "Input:  \"" << test << "\"\n";
        cout << "Output: \"" << result << "\"\n";
        cout << "-------------------------\n";
    }
    
    return 0;
}
