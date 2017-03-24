#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e7 + 5;
const int MOD = 1000000007;
int f[N], n, m;

long long int Pow(long long int a, int b)
{
	long long int sum = 1;
	while (b)
	{
		if (b&1)
		{
			sum *= a;
			sum %= MOD;
		}
		a = (a*a) % MOD;
		b >>= 1;
	}
	return sum;
}

void init()
{
	for (int i = 0; i <= n; ++i)
		f[i] = i;
}

int find(int a)
{
	int r = a;
	while (r != f[r]) r = f[r];
	int x = a, y;
	while (x != r)  y = f[x], f[x] = r, x = y;
	return r;
}

void Union(int l, int r)
{
	int x = find(l), y = find(r);
	if (x != y) f[x] = y;
}

int main()
{
	while (cin >> n >> m)
	{
		int l, r, ans = 0;
		init();
		for (int i = 0; i < m; ++i)
		{
			cin >> l >> r;
			l--;
			int x = find(l), y = find(r);
			if (x != y) Union(l, r), ++ans;
		}
		cout << Pow(26, n - ans) % MOD << endl;
	}
}