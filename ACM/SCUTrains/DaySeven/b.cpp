#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX = 2e5+1;
int a[MAX], n;

int solve(int x)
{
	int ret = 0, p = x;
	while (p < 10e6 + 1)
	{
		p += x;
		int k = lower_bound(a, a+n, p) - a;
		if (k == 0)
			continue;
		else 
			k--;

		if (a[k] <= x)
			continue;
		
		ret = max(ret, a[k] % x);
	}
	return ret;
}

int main()
{
	cin >> n;
	for (int i =0; i < n; ++i)
		cin >> a[i];
	sort(a, a + n);
	
	int ans = 0;
	for (int i = n-1; i >= 0; i--) 
	{
        if (ans >= a[i] - 1)
            break;
        if (i < n - 1 && a[i] == a[i+1])
            continue;
        ans = max(ans, solve(a[i]));
    }
	cout << ans;
	return 0;
}