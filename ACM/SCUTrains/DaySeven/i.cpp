#include <cstdio>
#include <iostream>

using namespace std;

long long int l, r, k;
int main()
{
	scanf("%I64d%I64d%I64d", &l, &r, &k);
	if (r - l + 1 <= 4)
	{
		long long int ans=0x3f3f3f3f3f3f3f3f;
		long long int m=r-l+1;  
        long long int sig=0;  
		
        for(long long int i=1; i<(1LL<<m); i++)  
        {  
            long long int temp=0;  
            long long int wei=0;  
            long long int si=i;  
            while(si)  
            {  
                wei++;  
                si=si&(si-1);  
            }  
            if(wei>k) continue;  
            for(long long int j=0;j<m;j++)  
            {  
                if(i&(1LL<<j))  
                {  
                    temp^=l+j;  
                }  
            }  
            if(temp<ans)  
            {  
                ans=temp;  
                sig=i;  
            }  
        }  
        cout<<ans<<endl;  
        long long int wei=0;  
        long long int tsig=sig;  
        while(tsig)  
        {  
            wei++;  
            tsig=tsig&(tsig-1);  
        }  
        cout<<wei<<endl;  
        for(long long int i=0;i<m;i++)  
        {  
            if(sig&(1<<i))  
            {  
                cout<<l+i<<" ";  
            }  
        }  
        cout<<endl;  
        return 0;
	}
	else if (k > 3)
	{
		if (l&1)
			l++;
		printf("0\n4\n%I64d %I64d %I64d %I64d\n", l, l+1, l+2, l+3);
		return 0;
	}
	else if (k == 3)
	{
		long long int x = 1;
		while (x <= l) x <<= 1;

		if ((x | (x>>1)) <= r) 
		{
			printf("0\n3\n");
			printf("%I64d %I64d %I64d\n", l, x | (x>>1), (x | (x>>1)) ^ l);
			return 0;
		}

		printf("1\n2\n");
		if (l&1)
			l++;
		printf("%I64d %I64d\n", l, l+1);
	}
	else if(k == 1)  
	{  
		printf("%I64d\n1\n%I64d", l, l); 
	}  
	else if (k == 2) 
	{
        if (l&1)
            l++;
        printf("1\n2\n%I64d %I64d\n", l, l+1);
    }
	return 0;
}
