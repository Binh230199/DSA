#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Approach 1: Depth-based Distribution (Counter)
class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> result(seq.length());
        int depth = 0;
        
        for (int i = 0; i < seq.length(); i++) {
            if (seq[i] == '(') {
                // Assign to group based on current depth
                result[i] = depth % 2;
                depth++;
            } else { // seq[i] == ')'
                depth--;
                // Assign to same group as matching opening
                result[i] = depth % 2;
            }
        }
        
        return result;
    }
};

void printVector(const vector<int>& vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ",";
    }
    cout << "]";
}

int main() {
    cout << "Approach 1: Depth-based Distribution (Counter)" << endl;
    cout << "Time: O(n), Space: O(1)" << endl << endl;
    
    Solution sol;
    
    vector<string> testCases = {
        "(()())",
        "()(())()",
        "(((())))",
        "()",
        "(())",
        "((()))",
        "(()()())",
        "(()(()))",
        "()()()",
        "(((()))))"
    };
    
    vector<vector<int>> expected = {
        {0,1,1,1,1,0},
        {0,0,0,1,1,0,1,1},
        {0,1,0,1,0,1,0,1},
        {0,0},
        {0,1,1,0},
        {0,1,0,1,1,0},
        {0,1,1,0,1,1,0,1,1,0},
        {0,1,1,0,1,0,1,0},
        {0,0,1,1,0,0},
        {0,1,0,1,0,1,0,1,0,1}
    };
    
    cout << "Testing Maximum Nesting Depth of Two Valid Parentheses Strings:" << endl;
    cout << "================================================================" << endl;
    
    for (int i = 0; i < testCases.size(); i++) {
        string seq = testCases[i];
        vector<int> result = sol.maxDepthAfterSplit(seq);
        
        cout << "Test Case " << i + 1 << ":" << endl;
        cout << "Input:    \"" << seq << "\"" << endl;
        cout << "Output:   ";
        printVector(result);
        cout << endl;
        cout << "Expected: ";
        printVector(expected[i]);
        cout << endl;
        
        // Verify the result is valid (both groups form valid parentheses)
        string groupA = "", groupB = "";
        for (int j = 0; j < seq.length(); j++) {
            if (result[j] == 0) {
                groupA += seq[j];
            } else {
                groupB += seq[j];
            }
        }
        
        // Check if both groups are valid parentheses strings
        auto isValid = [](const string& s) {
            int count = 0;
            for (char c : s) {
                if (c == '(') count++;
                else count--;
                if (count < 0) return false;
            }
            return count == 0;
        };
        
        bool validA = isValid(groupA);
        bool validB = isValid(groupB);
        
        cout << "Group A:  \"" << groupA << "\" - " << (validA ? "Valid" : "Invalid") << endl;
        cout << "Group B:  \"" << groupB << "\" - " << (validB ? "Valid" : "Invalid") << endl;
        cout << "Status:   " << (validA && validB ? "PASS" : "FAIL") << endl;
        cout << "-----------------------------------------" << endl;
    }
    
    return 0;
}
