#include <iostream>
#include<cmath>  
#include<algorithm>  
using namespace std;  
int L[505], M[505], N[505];
int buff[250025];
int main()
{
	int l, m, n, s, index = 0;
	bool isOk = false;
	while (scanf("%d%d%d",&l,&m,&n)!=EOF)
	{
		int i = 0;
		for(i=0;i<k;i++)  
			scanf("%d",&L[i]);  
		for(i=0;i<m;i++)  
			scanf("%d",&M[i]);  
		for(i=0;i<n;i++)  
			scanf("%d",&N[i]);  
		
		i=0;
		for (int a = 0; a < l; a++)
			for (int b = 0; b < m; b++)
				buff[i++] = L[a] + M[b];
		
		sort(buff,buff+i);  

		cin>>s;
		cout<<"Case "<<++index<<":\n";
		while (s--)
		{
			int x; cin>>x; isOk = false;
			for (int c = 0; c < n; c++)
			{
				int begin = 0, end = i-1, half;
				while (begin <= end)
				{
					half = (begin+end)/2;
					if (N[c]+buff[half] == x){isOk = true;break;}
					else if (N[c]+buff[half] > x) end = half-1;
					else if (N[c]+buff[half] < x) begin = half+1;
				}
				if (isOk) break;
			}
			if (isOk) cout<<"YES\n";
			else cout<<"NO\n";
		}
	}
	return 0;
}
