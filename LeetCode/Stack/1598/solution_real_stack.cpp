#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

// Approach 3: Real stack with folder names
class Solution {
public:
    int minOperations(vector<string>& logs) {
        stack<string> folderStack;
        
        for (const string& log : logs) {
            if (log == "../") {
                if (!folderStack.empty()) {
                    folderStack.pop();
                }
            } else if (log != "./") {
                folderStack.push(log);
            }
        }
        
        return folderStack.size();
    }
};

int main() {
    cout << "Approach 3: Real stack with folder names" << endl;
    cout << "Time: O(n), Space: O(n)" << endl << endl;
    
    Solution sol;
    
    vector<vector<string>> testCases = {
        {"d1/","d2/","../","d21/","./"},
        {"d1/","d2/","./","d3/","../","d31/"},
        {"d1/","../","../","../"}
    };
    
    vector<int> expected = {2, 3, 0};
    
    cout << "Testing Real Stack Solution:\n";
    cout << "============================\n";
    
    for (int i = 0; i < testCases.size(); i++) {
        int result = sol.minOperations(testCases[i]);
        cout << "Test Case " << i + 1 << ":\n";
        cout << "Input:    [";
        for (int j = 0; j < testCases[i].size(); j++) {
            cout << "\"" << testCases[i][j] << "\"";
            if (j < testCases[i].size() - 1) cout << ",";
        }
        cout << "]\n";
        cout << "Output:   " << result << "\n";
        cout << "Expected: " << expected[i] << "\n";
        cout << "Status:   " << (result == expected[i] ? "PASS" : "FAIL") << "\n";
        cout << "-------------------------------------\n";
    }
    
    return 0;
}
