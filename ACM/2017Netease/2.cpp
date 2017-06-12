#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
    int w, x, y, z;
    while (cin >> w >> x >> y >> z) {
        set<double> sets;
        for (int i = w; i <= x; ++i) 
            for (int j = y; j <= z; ++j) {
                sets.insert(static_cast<double>(i)/j);
            }
        cout << sets.size() << endl;
    }
    return 0;
}