#include <iostream>
#include <vector>
using namespace std;

// Approach 2: Count-based solution (Optimized)
class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        int count0 = 0, count1 = 0;
        
        // Count preferences
        for (int student : students) {
            if (student == 0) count0++;
            else count1++;
        }
        
        // Process sandwiches
        for (int sandwich : sandwiches) {
            if (sandwich == 0) {
                if (count0 > 0) {
                    count0--;
                } else {
                    break; // No more students want circular sandwiches
                }
            } else {
                if (count1 > 0) {
                    count1--;
                } else {
                    break; // No more students want square sandwiches
                }
            }
        }
        
        return count0 + count1;
    }
};

int main() {
    cout << "Approach 2: Count-based solution (Optimized)" << endl;
    cout << "Time: O(n), Space: O(1)" << endl << endl;
    
    Solution sol;
    
    vector<vector<int>> studentsTests = {
        {1,1,0,0},
        {1,1,1,0,0,1}
    };
    
    vector<vector<int>> sandwichesTests = {
        {0,1,0,1},
        {1,0,0,0,1,1}
    };
    
    vector<int> expected = {0, 3};
    
    cout << "Testing Count-based Solution:\n";
    cout << "=============================\n";
    
    for (int i = 0; i < studentsTests.size(); i++) {
        vector<int> students = studentsTests[i];
        vector<int> sandwiches = sandwichesTests[i];
        int result = sol.countStudents(students, sandwiches);
        
        cout << "Test Case " << i + 1 << ":\n";
        cout << "Students:    [";
        for (int j = 0; j < students.size(); j++) {
            cout << students[j];
            if (j < students.size() - 1) cout << ",";
        }
        cout << "]\n";
        cout << "Sandwiches:  [";
        for (int j = 0; j < sandwiches.size(); j++) {
            cout << sandwiches[j];
            if (j < sandwiches.size() - 1) cout << ",";
        }
        cout << "]\n";
        cout << "Output:      " << result << "\n";
        cout << "Expected:    " << expected[i] << "\n";
        cout << "Status:      " << (result == expected[i] ? "PASS" : "FAIL") << "\n";
        cout << "-----------------------------------------\n";
    }
    
    return 0;
}
