#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;
const int maxn = 1e6 + 5;
typedef double db;
int a[maxn];
int n, l, t;
int main()
{
    scanf("%d%d%d", &n, &l, &t);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    double ans = 0;
    int k = 2*t/l, c = 2*t%l;
	//cout << k << ' ' << c << endl;
    for(int i = 0; i < n; i++) {
        int w = a[i] - c;
        int cnt = 0;
        if(w >= 0) {
            cnt = i - (lower_bound(a, a + n, w) - a);
        } else {
            cnt += i;
            cnt += n - (lower_bound(a, a + n, l + w) - a);
        }
        ans += 0.5*0.5*k*(n - 1) + 0.5*0.5*cnt;
    }
    cout.setf(ios::fixed);
    cout << setprecision(9) << ans << endl;
    return 0;
}