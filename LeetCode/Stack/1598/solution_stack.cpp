#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Approach 1: Stack simulation with vector<bool> (Your solution)
class Solution {
public:
    int minOperations(vector<string>& logs) {
        vector<bool> st;

        for (const auto& l : logs) {
            if (l == "../") {
                if (!st.empty()) {
                    st.pop_back();
                }
            } else if (l != "./") {
                st.push_back(true);
            }
        }

        return st.size();
    }
};

int main() {
    cout << "Approach 1: Stack simulation with vector<bool>" << endl;
    cout << "Time: O(n), Space: O(n)" << endl << endl;
    
    Solution sol;
    
    vector<vector<string>> testCases = {
        {"d1/","d2/","../","d21/","./"},
        {"d1/","d2/","./","d3/","../","d31/"},
        {"d1/","../","../","../"}
    };
    
    vector<int> expected = {2, 3, 0};
    
    cout << "Testing Crawler Log Folder Solution:\n";
    cout << "=====================================\n";
    
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
