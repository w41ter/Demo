#include <stdio.h>
#include <algorithm>

using namespace std;

const int MAXN = 500500;
int a[MAXN],n,len,ans;
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
       scanf("%d",&a[i]);
    for(int i=0;i<n;i++)
    {
        int k=i;
        len=0;
        while(a[k+1]!=a[k] && k<n-1){ len++; k++; }
        if(i!=k)
        {
            if(i!=k && a[i]==a[k]){
            	for(i++;i<k;i++) a[i]=a[k];
            }else if(i!=k){
                int j;
                for(j=1;j<=(k-i)/2;j++) a[j+i]=a[i];
                for(;j+i<k;j++) a[j+i]=a[k];
                i=k;
            }
        }
        ans=max(ans,len);
    }
    if(ans==n) ans--;
    printf("%d\n", ans/2);
    for(int i=0;i<n;i++)
    {
        if(i!=n-1)printf("%d ", a[i]);
        else printf("%d\n", a[i]);
    }
    return 0;
}