#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 3e5;
int rmq[N][32], can[N][32];
int A[N], _ans, n, res, _mid;

void RMQ_INIT(int n) //预处理->O(nlogn)
{
	for (int i = 0; i <= n; ++i) rmq[i][0] = A[i], can[i][0] = 1;
	for (int j = 1; (1 << j) <= n; j++)
		for (int i = 1; i + j - 1 <= n; ++i)
		{
			int a = rmq[i][j-1], b = rmq[i + (1 << (j-1))][j-1];
			rmq[i][j] = min(a, b);
			can[i][j] = (can[i][j-1] && can[i + (1 << (j-1))][j-1]);
			if (rmq[i][j] == 0)
				can[i][j] = 0;
			else
				can[i][j] = (can[i][j] && (a % rmq[i][j] == 0 || b % rmq[i][j] == 0));
		}
}

int RMQ(int l, int r)
{
	int k = 0; 
	while ((1 << (k+1)) <= r-l+1) k++;
	int a = can[l][k], b = can[r - (1<<k) + 1][k];
	return a && b;
}

int ok(int mid)
{
	for (int i = 1; i + mid <= n; ++i)
	{
		if (RMQ(i, i + mid))
		{
			printf("%d %d\n", i, i + mid);
			return 1;
		}
			
	}
	return 0;
}

int main()
{
	scanf("%d", &n);
	
	for (int i = 1; i <= n; ++i)
		scanf("%d", &A[i]);
	
	RMQ_INIT(n + 3);
	
	int l = 0, r = n - 1, mid;
	while (l <= r)
	{
		mid = l + (r-l>>1);
		if (ok(mid)) 
			l = mid + 1, _mid = mid;
		else
			r = mid - 1;
	}
	
	int ans = 0;
	for (int i = 1; i + _mid <= n; ++i)
	{
		if (RMQ(i, i + _mid))
			ans++;
	}
	
	printf("%d %d\n", ans, _mid);
	for (int i = 1; i + _mid <= n; ++i)
	{
		if (RMQ(i, i + _mid))
			printf("%d ", i);
	}
	return 0;
}