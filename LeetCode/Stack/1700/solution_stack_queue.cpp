#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// Approach 3: Stack and Queue simulation (Educational)
class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        stack<int> sandwichStack;
        queue<int> studentQueue;
        
        // Build stack (reverse order since stack is LIFO)
        for (int i = sandwiches.size() - 1; i >= 0; i--) {
            sandwichStack.push(sandwiches[i]);
        }
        
        // Build queue
        for (int student : students) {
            studentQueue.push(student);
        }
        
        int rotations = 0;
        
        while (!studentQueue.empty() && !sandwichStack.empty()) {
            int currentStudent = studentQueue.front();
            int currentSandwich = sandwichStack.top();
            
            if (currentStudent == currentSandwich) {
                // Student takes sandwich
                studentQueue.pop();
                sandwichStack.pop();
                rotations = 0; // Reset rotation counter
            } else {
                // Student goes to back of queue
                studentQueue.pop();
                studentQueue.push(currentStudent);
                rotations++;
                
                // If we've rotated through all students, no one wants current sandwich
                if (rotations == studentQueue.size()) {
                    break;
                }
            }
        }
        
        return studentQueue.size();
    }
};

int main() {
    cout << "Approach 3: Stack and Queue simulation (Educational)" << endl;
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
    
    cout << "Testing Stack and Queue Simulation:\n";
    cout << "===================================\n";
    
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
