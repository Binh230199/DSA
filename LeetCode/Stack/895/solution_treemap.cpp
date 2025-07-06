#include <iostream>
#include <map>
#include <stack>
using namespace std;

// Approach 5: Ordered Map (TreeMap equivalent)
class FreqStack {
private:
    map<int, int> freq;                    // value -> frequency
    map<int, stack<int>> buckets;          // frequency -> stack (ordered)
    
public:
    FreqStack() {}
    
    void push(int val) {
        freq[val]++;
        buckets[freq[val]].push(val);
    }
    
    int pop() {
        // Get highest frequency bucket
        auto it = buckets.rbegin();
        int val = it->second.top();
        it->second.pop();
        
        // Remove empty bucket
        if (it->second.empty()) {
            buckets.erase(it->first);
        }
        
        freq[val]--;
        if (freq[val] == 0) {
            freq.erase(val);
        }
        
        return val;
    }
};

int main() {
    cout << "Approach 5: Ordered Map (TreeMap)" << endl;
    cout << "Time: O(log k) push, O(log k) pop (k = unique frequencies)" << endl;
    cout << "Space: O(n)" << endl << endl;
    
    FreqStack fs;
    fs.push(5); fs.push(7); fs.push(5); 
    fs.push(7); fs.push(4); fs.push(5);
    
    cout << "Pop sequence: ";
    for (int i = 0; i < 6; i++) {
        cout << fs.pop() << " ";
    }
    cout << endl;
    
    return 0;
}
