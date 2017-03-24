#include <stdio.h> 
#include <string.h> 
#include <algorithm> 
#include <iostream>

using namespace std; 
 
#define N 505 
 
struct range 
{ 
    int a,b; 
	range(){}
    range(int _a,int _b):a(_a),b(_b){} 
    bool operator < (const range& s)const 
    { 
        return b < s.b || b == s.b && a < s.a; 
    } 
}S[N]; 
 
int num[N][N], dp[N]; 
 
int main() 
{ 
    int n,a,b; 
    while(~scanf("%d",&n)) 
    { 
        int m = 0; 
        memset(num, 0, sizeof(num)); 
        memset(dp, 0, sizeof(dp)); 
        for(int i=0; i < n; i++) 
        { 
            scanf("%d%d", &a, &b); 
            if(a + b > n - 1 || num[a + 1][n - b] == n - b - a) 
                continue; 
			
            if(!num[a + 1][n - b]) 
                S[m++] = range(a+1,n-b); 
            ++num[a+1][n-b]; 
        } 
        sort(S, S+m); 
        int ans = 0; 
        for(int i = 0; i < m; i++) 
        { 
            int mmax = 0; 
            for(int j = 0;j < i; j++) 
                if(S[j].b < S[i].a) 
                    mmax = max(mmax, dp[j]); 
            dp[i] = mmax + num[S[i].a][S[i].b]; 
            ans = max(ans, dp[i]); 
        } 
        printf("%d\n",ans); 
    } 
    return 0; 
} 