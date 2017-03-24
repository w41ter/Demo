#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
bool open[N];
int vis[N], c[N];

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 2; i <= n; ++i)
		if (c[i] == 0)
			for (int j = i; j <= n; j += i)
				c[j] = i;
		
Begin:		
	while (m--)
	{
		char op[2];
		int num;
		scanf("%s %d", op, &num);
		//printf("%s %d\n", op, num);
		if (op[0] == '+')
		{
			if (open[num])
			{
				printf("Already on\n");
				goto Begin;
			}
			for (int i = num; i > 1; i /= c[i]) 
				if (vis[c[i]] != 0)
				{
					printf("Conflict with %d\n", vis[c[i]]);
					goto Begin;
				}
			for (int i = num; i > 1; i /= c[i]) vis[c[i]] = num;
			open[num] = true;
			printf("Success\n");
			goto Begin;
		}
		else
		{
			if (!open[num]) 
			{
				printf("Already off\n");
				goto Begin;
			}
			open[num] = false;
			for (int i = num; i > 1; i /= c[i]) vis[c[i]] = 0;
			printf("Success\n");
			goto Begin;
		}
	}
	return 0;
}