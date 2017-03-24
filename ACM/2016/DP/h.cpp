#include <iostream>
#include <algorithm>
#include <string.h>
#include <set>

using namespace std;

long long int goods[40000], array[40000], total = 0;
int table[100005], queue[100005];

void insert(long long int a, long long int m) {
    long long int i = 1;
    while (m - i * 2 + 1 > 0) {
        goods[++total] = i * a;
        i <<= 1;
    }
    goods[++total] = (m - i + 1) * a;
}

int main() __attribute__((optimize("-O3")));

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        int A[105] = {0};
        
        total = 0;
        for (int i = 0; i < n; ++i) {
            cin >> A[i];
        }
        for (int i = 0; i < n; ++i) {
            long long int m;
            cin >> m;
            insert(A[i], m);
        }
        int length = 1;
        queue[0] = 0;
        memset(table, 0, sizeof(table));
        for (int i = 1; i <= total; ++i) {
            int index = length;
            for (int j = 0; j < length; ++j) {
                //cout << "length = " << j << " tmp = " << queue[j] + goods[i] << endl;
                long long int tmp = queue[j] + goods[i];
                if (tmp > k) continue;
                if (table[tmp] == 0) {
                    queue[index++] = tmp;
                    //cout << "queue [" << index-1 << "] = " << queue[index-1] << endl;
                    table[tmp] = 1;
                }
            }
            length = index;
        }
        
        if (table[k] != 0) 
            cout << "yes" << endl;
        else 
            cout << "no" << endl; 
    }
    return 0;
}