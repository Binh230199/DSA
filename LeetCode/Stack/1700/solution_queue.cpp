#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Approach 1: Queue simulation (Your solution)
class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        queue<int> q;
        for (int student : students) {
            q.push(student);
        }

        for (const auto& sw : sandwiches) {
            int qsz = q.size();
            int original_sz = qsz;

            while (qsz > 0) {
                int front = q.front();
                q.pop();
                qsz--;

                if (front != sw) {
                    q.push(front);
                } else {
                    break;
                }
            }

            // Compare the size of queue after process with original size
            // If return true, it means that there is no valid case anymore
            // Stop it
            if (original_sz == q.size()) break;
        }

        return q.size();
    }
};

int main() {
    cout << "Approach 1: Queue simulation (Your solution)" << endl;
    cout << "Time: O(n^2), Space: O(n)" << endl << endl;
    
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
    
    cout << "Testing Number of Students Unable to Eat:\n";
    cout << "=========================================\n";
    
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
