#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2 * 1e6 + 5;
char ori[N], str[N];
int p[N];

int main()
{
	std::ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--)
	{
		str[0] = '$';
		str[1] = '#';
		cin >> ori;
		int n = 2;
		for (int i = 0; ori[i]; ++i)
		{
			str[n++] = ori[i];
			str[n++] = '#';
		}
		
		int id = 0, ma = 0;
		for (int i = 1; i < n; ++i)
		{
			p[i] = 0;
			if (ma > i) p[i] = min(p[2*id-i], ma-i);
			else  p[i] = 1;
			while (str[i - p[i]] == str[i + p[i]]) p[i]++;
			if (i + p[i] > ma) ma = i + p[i], id = i;
		}
		int ans = 0;
		for (int i = 1; i < n; ++i)
			ans = max(ans, p[i] - 1);
		cout << ans << endl;
	}
}