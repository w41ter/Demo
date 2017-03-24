#include <iostream>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;
long long int  n,ans;

long long int pow(long long int a,long long int b)
{
    long long int r=1,base=a;
    while(b!=0)
    {
        if(b&1)
            r=(r*base)%MOD;
        base=(base*base)%MOD;
        b>>=1;
    }
    return r;
}

int main()
{
    cin >> n;
	if (n == 0)
	{
		printf("1");
		return 0;
	}
    ans=pow(2,n-1);
    ans=((ans*ans)%MOD*2+ans)%MOD;
    cout << ans;
    return 0;
}
