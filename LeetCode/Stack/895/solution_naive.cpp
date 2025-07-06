#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Approach 2: Naive - Store all elements with timestamps
class FreqStack {
private:
    vector<pair<int, int>> elements;  // {value, timestamp}
    unordered_map<int, int> freq;
    int timestamp;
    
public:
    FreqStack() : timestamp(0) {}
    
    void push(int val) {
        freq[val]++;
        elements.push_back({val, timestamp++});
    }
    
    int pop() {
        int maxFreq = 0, maxTime = -1, idx = -1;
        
        // Find element with max frequency, then max timestamp
        for (int i = 0; i < elements.size(); i++) {
            if (elements[i].first != -1) {  // not deleted
                int val = elements[i].first;
                int time = elements[i].second;
                
                if (freq[val] > maxFreq || 
                    (freq[val] == maxFreq && time > maxTime)) {
                    maxFreq = freq[val];
                    maxTime = time;
                    idx = i;
                }
            }
        }
        
        int result = elements[idx].first;
        elements[idx].first = -1;  // mark as deleted
        freq[result]--;
        
        return result;
    }
};

int main() {
    cout << "Approach 2: Naive Solution" << endl;
    cout << "Time: O(n) push, O(n) pop" << endl;
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
