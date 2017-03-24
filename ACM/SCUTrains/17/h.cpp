#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int n, x, y, a, b;

const int MOD = 1e9 + 7;
const int N = 10000+10;
long long int f[N];
bool cana, canb;

void slove(int k, int l, int r)
{
	memset(f, 0, sizeof(f));
	f[l] = k;
	for (int i = l; i <= r; ++i)
	{
		if (i + x < N)
			f[i + x] = (f[i] + f[i + x]) % MOD;
		if (i + y < N)
			f[i + y] = (f[i] + f[i + y]) % MOD;
	}
}

int main()
{
	while (cin >> n >> x >> y >> a >> b)
	{
		if (a > b) swap(a, b);
		slove(1, 0, a);
		slove(f[a], a, b);
		slove(f[b], b, n);
		cout << f[n] % MOD << endl;
	}
	return 0;
}