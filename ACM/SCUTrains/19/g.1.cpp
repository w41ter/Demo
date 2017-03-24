#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 505;

struct Range {
	int l, r;
	Range(){}
	Range(int a, int b) : l(a), r(b) {}
	bool operator < (const Range& s)const 
    { 
        return r < s.r || r == s.r && l < s.l; 
    } 
} r[N];

int num[N][N], dp[N]; 
 
int main() 
{ 
    int n,a,b; 
    while(cin >> n) 
    { 
        int m = 0; 
        memset(num, 0, sizeof(num)); 
        memset(dp, 0, sizeof(dp)); 
        for(int i = 0; i < n; i++) 
        { 
            cin >> a >> b;
            if(a + b > n - 1 || num[a + 1][n - b] == n - b - a) 
                continue; 
			
            if(!num[a + 1][n - b]) 
                r[m++].l = a + 1, r[m].r = n - b;
            ++num[a + 1][n - b]; 
        } 
        sort(r, r + m); 
        int ans = 0; 
        for(int i = 0; i < m; i++) 
        { 
            int mmax = 0; 
            for(int j = 0;j < i; j++) 
                if(r[j].r < r[i].l) 
                    mmax = max(mmax, dp[j]); 
            dp[i] = mmax + num[r[i].l][r[i].r]; 
            ans = max(ans, dp[i]); 
        } 
        cout << ans << endl;
    } 
    return 0; 
} 