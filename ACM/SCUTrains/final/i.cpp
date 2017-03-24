#include <iostream>
#include <cstdio>
#include <cstring>
#define MAXN 999999
using namespace std;
const int button[]={2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
int ans[MAXN];
int number[5050];
int t,n,m;
int main()
{
    scanf("%d",&t);
    int d;
    while(t--)
    {
        char s[10];
        memset(ans, 0, sizeof(ans));
        scanf("%d %d",&n,&m);
        for(int i=0;i<n;i++)
            scanf("%d",&number[i]);
        for(int i=0;i<m;i++)
        {
            cin>>s;
            for(int j=0;j<strlen(s);j++)
                s[j]=button[s[j]-'a']+'0';
            sscanf(s, "%d",&d);
            ans[d]++;
        }
        for(int i=0;i<n;i++)
            printf("%d\n",ans[number[i]]);
    }
    return 0;
}