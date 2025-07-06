# 1700. Number of Students Unable to Eat Lunch

## Intuition
This problem simulates a cafeteria scenario where students form a queue and can only eat if the top sandwich matches their preference. The key insight is that we need to track when no progress can be made - when all remaining students have cycled through but none can eat the current sandwich.

## Approach

### Approach 1: Queue Simulation (Direct simulation)
- Use a queue to represent students waiting in line
- For each sandwich, try to find a student who wants it
- If a full cycle occurs without any student taking the sandwich, stop
- Count remaining students in queue

### Approach 2: Count-Based Approach (Optimized)
- Count how many students want each type of sandwich (0s and 1s)
- Process sandwiches in order, decrementing counters
- If we need a sandwich type but no students want it, stop
- Return sum of remaining counts

### Approach 3: Stack and Queue Simulation (Educational)
- Use explicit stack for sandwiches and queue for students
- Similar to approach 1 but with clearer data structure separation
- Helps understand the stack/queue relationship in the problem

## Complexity

### Approach 1: Queue Simulation
- Time complexity: $$O(n^2)$$ - In worst case, each student cycles through queue n times
- Space complexity: $$O(n)$$ - Queue stores all students

### Approach 2: Count-Based
- Time complexity: $$O(n)$$ - Single pass through sandwiches
- Space complexity: $$O(1)$$ - Only counters used

### Approach 3: Stack and Queue
- Time complexity: $$O(n^2)$$ - Similar to approach 1
- Space complexity: $$O(n)$$ - Stack and queue storage

## Code

### Approach 1: Queue Simulation
```cpp
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

            if (original_sz == q.size()) break;
        }

        return q.size();
    }
};
```

### Approach 2: Count-Based
```cpp
class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        int count0 = 0, count1 = 0;
        
        // Count students' preferences
        for (int student : students) {
            if (student == 0) count0++;
            else count1++;
        }
        
        // Process sandwiches in order
        for (int sandwich : sandwiches) {
            if (sandwich == 0) {
                if (count0 > 0) count0--;
                else break; // No student wants this sandwich
            } else {
                if (count1 > 0) count1--;
                else break; // No student wants this sandwich
            }
        }
        
        return count0 + count1;
    }
};
```

### Approach 3: Stack and Queue
```cpp
class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        stack<int> sandwichStack;
        queue<int> studentQueue;
        
        // Initialize stack (reverse order for correct processing)
        for (int i = sandwiches.size() - 1; i >= 0; i--) {
            sandwichStack.push(sandwiches[i]);
        }
        
        // Initialize queue
        for (int student : students) {
            studentQueue.push(student);
        }
        
        int consecutiveNoMatch = 0;
        
        while (!sandwichStack.empty() && !studentQueue.empty()) {
            int currentSandwich = sandwichStack.top();
            int currentStudent = studentQueue.front();
            
            if (currentStudent == currentSandwich) {
                sandwichStack.pop();
                studentQueue.pop();
                consecutiveNoMatch = 0;
            } else {
                studentQueue.pop();
                studentQueue.push(currentStudent);
                consecutiveNoMatch++;
                
                // If all students have been checked and none match
                if (consecutiveNoMatch == studentQueue.size()) {
                    break;
                }
            }
        }
        
        return studentQueue.size();
    }
};
```

## Application in Real World

1. **Resource Allocation Systems**: Similar to job scheduling where tasks have specific requirements and resources must match
2. **Cafeteria Management**: Direct application in school/corporate cafeterias for meal planning
3. **Inventory Management**: When items must be distributed in specific order but customers have preferences
4. **Queue Management**: Any system where service order matters but preferences create bottlenecks
5. **Load Balancing**: Distributing tasks to workers with specific capabilities

## Related Problems

1. **622. Design Circular Queue**: Queue data structure implementation
2. **933. Number of Recent Calls**: Queue-based time window problems
3. **225. Implement Stack using Queues**: Stack/queue conversion
4. **232. Implement Queue using Stacks**: Queue/stack conversion
5. **1672. Richest Customer Wealth**: Array processing with preferences
6. **1046. Last Stone Weight**: Priority-based processing (heap)
7. **649. Dota2 Senate**: Circular queue with elimination
8. **950. Reveal Cards In Increasing Order**: Queue simulation problems
