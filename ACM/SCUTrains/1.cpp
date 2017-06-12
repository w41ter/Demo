#include <bits/stdc++.h>

using namespace std;

void calculate(long long *a, long long int num) {
    if (num <= 0) return ;
    if (num < 10) {
        for (int i = 1; i <= num; ++i) {
            a[i] = 1;
        }
        return ;
    }

    int bit = 1, k = 0;
    while (bit * 10 <= num) bit *= 10, k++;

    int high = num / bit;
    // 1000 100个 100十 100百
    for (int i = 0; i < 10; ++i) {
        a[i] = high * bit * k / 10;
    }

    // 千分位出现 1000次
    for (int i = 1; i < high; ++i) {
        a[i] += bit;
    }

    // 剩余部分
    int low = num % bit;
    a[high] += low + 1;
    long long int res[10] = { 0ll };
    calculate(res, low);
    for (int i = 0; i < 10; ++i) {
        a[i] += res[i];
    }
}

int main() {
    long long int M, N;
    while (cin >> M >> N) {
        long long a[10] = { 0ll };
        long long b[10] = { 0ll };
        calculate(a, M-1);
        calculate(b, N);
        for (int i = 0; i < 10; ++i) {
            cout << b[i] - a[i] << ' ';
        }
        cout << endl;
    }
    return 0;
}