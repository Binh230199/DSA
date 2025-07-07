#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

// Approach 2: Stack-based Tracking
class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> result(seq.length());
        stack<int> groupStack;
        
        for (int i = 0; i < seq.length(); i++) {
            if (seq[i] == '(') {
                // Assign to group based on current stack depth
                int group = groupStack.size() % 2;
                result[i] = group;
                groupStack.push(group);
            } else { // seq[i] == ')'
                // Assign to same group as matching opening
                result[i] = groupStack.top();
                groupStack.pop();
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
    cout << "Approach 2: Stack-based Tracking" << endl;
    cout << "Time: O(n), Space: O(n)" << endl << endl;
    
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
        
        // Calculate depth of each group
        auto getDepth = [](const string& s) {
            int depth = 0, maxDepth = 0;
            for (char c : s) {
                if (c == '(') depth++;
                else depth--;
                maxDepth = max(maxDepth, depth);
            }
            return maxDepth;
        };
        
        bool validA = isValid(groupA);
        bool validB = isValid(groupB);
        int depthA = getDepth(groupA);
        int depthB = getDepth(groupB);
        
        cout << "Group A:  \"" << groupA << "\" - " << (validA ? "Valid" : "Invalid") << " (depth: " << depthA << ")" << endl;
        cout << "Group B:  \"" << groupB << "\" - " << (validB ? "Valid" : "Invalid") << " (depth: " << depthB << ")" << endl;
        cout << "Max Depth: " << max(depthA, depthB) << endl;
        cout << "Status:   " << (validA && validB ? "PASS" : "FAIL") << endl;
        cout << "-----------------------------------------" << endl;
    }
    
    return 0;
}
