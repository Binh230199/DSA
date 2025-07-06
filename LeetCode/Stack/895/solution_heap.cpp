#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

// Approach 3: Priority Queue (Max Heap)
class FreqStack {
private:
    struct Element {
        int val, freq, timestamp;
        
        bool operator<(const Element& other) const {
            if (freq != other.freq) return freq < other.freq;
            return timestamp < other.timestamp;
        }
    };
    
    priority_queue<Element> pq;
    unordered_map<int, int> freq;
    int timestamp;
    
public:
    FreqStack() : timestamp(0) {}
    
    void push(int val) {
        freq[val]++;
        pq.push({val, freq[val], timestamp++});
    }
    
    int pop() {
        while (!pq.empty()) {
            Element top = pq.top();
            pq.pop();
            
            // Check if this element is still valid
            if (top.freq == freq[top.val]) {
                freq[top.val]--;
                return top.val;
            }
        }
        return -1;
    }
};

int main() {
    cout << "Approach 3: Priority Queue Solution" << endl;
    cout << "Time: O(log n) push, O(log n) pop" << endl;
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
