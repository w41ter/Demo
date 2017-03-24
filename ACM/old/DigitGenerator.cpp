#include <stdio.h>
#include <string.h>
#define MAX 100005

int ans[MAX];

int main()
{
	int T, n;
	memset(ans, 0, sizeof(ans));
	for (n = 0; n < MAX; n++)
	{
		int x = n, y = n;
		while (x > 0) {y += x % 10; x /= 10; }
		if (ans[y] == 0 || ans[y] > n) ans[y] = n;
	}
	
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		printf("%d\n", ans[n]);
	}
	
	return 0;
}
