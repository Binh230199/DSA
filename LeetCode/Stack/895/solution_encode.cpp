#include <iostream>
#include <stack>
#include <unordered_map>
using namespace std;

// Approach 4: Encode Technique - Single Stack
class FreqStack {
private:
    stack<int> st;
    unordered_map<int, int> freq;
    int maxFreq;
    
    // Encode frequency into value: (freq << 16) | value
    int encode(int val, int frequency) {
        return (frequency << 16) | (val & 0xFFFF);
    }
    
    int decodeValue(int encoded) {
        return encoded & 0xFFFF;
    }
    
    int decodeFreq(int encoded) {
        return encoded >> 16;
    }
    
public:
    FreqStack() : maxFreq(0) {}
    
    void push(int val) {
        freq[val]++;
        maxFreq = max(maxFreq, freq[val]);
        st.push(encode(val, freq[val]));
    }
    
    int pop() {
        int encoded = st.top();
        st.pop();
        
        int val = decodeValue(encoded);
        int frequency = decodeFreq(encoded);
        
        freq[val]--;
        if (frequency == maxFreq) {
            maxFreq--;
            // Update maxFreq by scanning stack
            stack<int> temp = st;
            maxFreq = 0;
            while (!temp.empty()) {
                maxFreq = max(maxFreq, decodeFreq(temp.top()));
                temp.pop();
            }
        }
        
        return val;
    }
};

int main() {
    cout << "Approach 4: Encode Technique - Single Stack" << endl;
    cout << "Time: O(1) push, O(n) pop (worst case)" << endl;
    cout << "Space: O(n) - only one stack" << endl << endl;
    
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
