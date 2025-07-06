#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

class FreqStack {
private:
    unordered_map<int, int> freq;           // value -> frequency
    unordered_map<int, stack<int>> buckets; // frequency -> stack of values
    int maxFreq;
    
public:
    FreqStack() : maxFreq(0) {}
    
    void push(int val) {
        freq[val]++;
        buckets[freq[val]].push(val);
        maxFreq = max(maxFreq, freq[val]);
    }
    
    int pop() {
        int val = buckets[maxFreq].top();
        buckets[maxFreq].pop();
        
        freq[val]--;
        if (buckets[maxFreq].empty()) {
            maxFreq--;
        }
        
        return val;
    }
};

int main() {
    FreqStack fs;
    
    // Test case: [5,7,5,7,4,5]
    fs.push(5); fs.push(7); fs.push(5); 
    fs.push(7); fs.push(4); fs.push(5);
    
    cout << fs.pop() << " ";  // 5 (freq=3)
    cout << fs.pop() << " ";  // 7 (freq=2) 
    cout << fs.pop() << " ";  // 5 (freq=2)
    cout << fs.pop() << " ";  // 4 (freq=1)
    cout << fs.pop() << " ";  // 7 (freq=1)
    cout << fs.pop() << endl; // 5 (freq=1)
    
    return 0;
}
