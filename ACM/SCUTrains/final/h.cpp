#include <iostream>
#include <cstring>
#include <cstdio>
#define MAXN 220
#define MIN(a,b) (a>b?b:a)
using namespace std;
int dp[MAXN][MAXN];
int a[MAXN],b[MAXN];
int main()
{
    int T,N;
    scanf("%d",&T);
    for(int cas = 1;cas <= T;cas++)
    {
        memset(dp, 0, sizeof(dp));
        scanf("%d",&N);
        for(int i=1;i<=N;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=N;i++)
            scanf("%d",&b[i]);
        b[0]=b[N+1]=0;
        for (int l=0;l<=N;l++)
        {
            for (int i=1;i<=N+1-l;i++)
            {
                int j = i+l;
                dp[i][j]=99999999;
                for (int k=i; k<=j; k++)
                {
                    dp[i][j] = MIN(dp[i][j], dp[i][k-1]+dp[k+1][j]+a[k]+b[i-1]+b[j+1]);
                }
            }
        }
        
        printf("Case #%d: %d\n",cas,dp[1][N]);
    }
    return 0;
}