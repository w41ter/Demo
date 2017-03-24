#include <iostream>
#include <string.h>

using namespace std;

long long int dp[1000010];
int a[1000010],m[1000010];
int n,k,T;

int main()
{
    cin >> T; 
    while(T--)
    {
        cin >> n >> k;
        for(int i=0;i<n;i++)
            cin >> a[i];
        for(int i=0;i<n;i++)
            cin >> m[i];
        
        memset(dp, -1ll, sizeof(dp));
        dp[0]=0;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<=k;j++)
            {
                if(dp[j]>=0ll)
                    dp[j]=m[i];
                else if(j<a[i]||dp[j-a[i]]<=0ll)
                    dp[j]=-1;
                else
                    dp[j]=dp[j-a[i]]-1ll;
            }
        }
        
        if(dp[k]>=0ll) cout << "yes" << endl;
        else cout << "no" << endl;
        
        n=0;k=0;
        memset(a,0,sizeof(a));
        memset(m,0,sizeof(m));
    }
    return 0;
}