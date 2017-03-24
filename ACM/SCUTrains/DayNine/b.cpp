#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
int a[N], suma, b[N], sumb, n, m, res[N], total;
bool ans[N];

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &res[i]);
		if (res[i] < 0)
		{
			b[abs(res[i])]++;
			sumb++;
		}
		else
		{
			a[res[i]]++;
			suma++;
		}
	}
	
	for (int i = 1; i <= n; ++i)
	{
		int am = a[i] + sumb - b[i];
		if (am == m)
			ans[i] = true, total++;
		else
			ans[i] = false;
	}
	
	for (int i = 1; i <= n; ++i)
	{
		if (res[i] > 0)
		{
			if (ans[res[i]])
			{
				if (total == 1)
					printf("Truth\n");
				else
					printf("Not defined\n");
			}
			else
			{
				printf("Lie\n");
			}				
		}
		else
		{
			if (ans[abs(res[i])])
			{
				if (total == 1)
					printf("Lie\n");
				else
					printf("Not defined\n");
			}
			else
				printf("Truth\n");
		}
	}
	return 0;
}