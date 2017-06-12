#include <bits/stdc++.h>

using namespace std;

struct hiho {
    int hc = 0;
    int ic = 0;
    int oc = 0;
    queue<int> pos;
    
    bool isHiho() const {
        return hc >= 2 && ic >= 1 && oc >=1;
    }
    
    bool isEmpty() const {
        return hc == 0 && ic == 0 && oc == 0;
    }
    
    int length(int i) const {
        return pos.back() - pos.front() + 1;
    }
    
    void push(char c, int idx) {
        if (c == 'h') hc++;
        else if (c == 'i') ic++;
        else if (c == 'o') oc++;
        else return;
        pos.push(idx);
        //std::cout << "push " << c << " at " << idx << endl;
    }
    
    void pop(const string &str) {
        char c = str[pos.front()];
        if (c == 'h') hc--;
        else if (c == 'i') ic--;
        else if (c == 'o') oc--;
        //cout << "pop " << c << " at " << pos.front() << endl;
        pos.pop();
    }
};

int main() {
    string str;
    while (getline(cin, str)) {
        hiho record;
        int result = INT_MAX;
        for (int i = 0; i < str.size(); ++i) {
            record.push(str[i], i);
            if (record.isHiho()) {
                result = min(record.length(i), result);
                record.pop(str);
            }
        }
        if (result == INT_MAX) 
            cout << -1 << endl;
        else
            cout << result << endl;
    }
    return 0;
}    

