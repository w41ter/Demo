#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int MAX = 1e5 + 5;
int m, n, w, a[MAX], b[MAX];

bool ok(int x)
{
	memset(b, 0, sizeof(b));
	int c = 0, d = m;
	for (int i = 0; i < n; i++)
	{
		c += b[i];
		if (a[i] + c < x)
		{
			int p = x - a[i] - c;
			if (d < p)
				return false;
			d -= p;
			c += p;
			if (i + w < n)
				b[i + w] -= p;
			else
				b[n] -= p;
		}
	}
	return true;
}

int main()
{
	int top = 0, low = 0x7fffffff;
	scanf("%d%d%d", &n, &m, &w);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &a[i]);
		top = max(top, a[i]);
		low = min(low, a[i]);
	}
	
	top += m;
	int ans = low;
	while (low <= top)
	{
		int mid = low + ((top - low) >> 1);
		//printf("cur top is %d, and low is %d, and mid is %d\n", top, low, mid);
		
		if (ok(mid))
		{
			ans = max(ans, mid);
			low = mid + 1;
		}
		else
		{
			top = mid - 1;
		}
	}
	printf("%d", ans);
}