#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

// Approach 3: Real stack with in-place processing
class Solution {
public:
    string simplifyPath(string path) {
        stack<string> st;
        int i = 0;
        int n = path.length();
        
        while (i < n) {
            // Skip slashes
            while (i < n && path[i] == '/') {
                i++;
            }
            
            // Extract component
            string component = "";
            while (i < n && path[i] != '/') {
                component += path[i];
                i++;
            }
            
            // Process component
            if (component == "..") {
                if (!st.empty()) {
                    st.pop();
                }
            } else if (component != "" && component != ".") {
                st.push(component);
            }
        }
        
        // Build result from stack
        string result = "";
        while (!st.empty()) {
            result = "/" + st.top() + result;
            st.pop();
        }
        
        return result.empty() ? "/" : result;
    }
};

int main() {
    cout << "Approach 3: Real stack with in-place processing" << endl;
    cout << "Time: O(n), Space: O(n)" << endl << endl;
    
    Solution sol;
    
    vector<string> testCases = {
        "/home/",
        "/home//foo/",
        "/home/user/Documents/../Pictures",
        "/../",
        "/.../a/../b/c/../d/./"
    };
    
    cout << "Testing Stack-based Solution:\n";
    cout << "=============================\n";
    
    for (const string& test : testCases) {
        string result = sol.simplifyPath(test);
        cout << "Input:  \"" << test << "\"\n";
        cout << "Output: \"" << result << "\"\n";
        cout << "-------------------------\n";
    }
    
    return 0;
}
