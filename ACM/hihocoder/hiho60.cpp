#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2105;
char s1[N], s2[N];
int dp[N][N], f[N][N];

int main()
{
	std::ios::sync_with_stdio(false);
	cin >> s1 >> s2;
	int n = strlen(s1);
	int m = strlen(s2);
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= m; ++j)
		{
			if (s1[i-1] == s2[j-1])
				f[i][j] = f[i-1][j-1] + 1;
			else
				f[i][j] = 0;
		}
		
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
		{
			dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
			if (f[i][j] >= 3)
			{
				for (int k = 3; k <= f[i][j]; ++k)
					dp[i][j] = max(dp[i][j], dp[i-k][j-k] + k);
			}
		}
	
	// for (int i = 0; i <= n; ++i)
	// {
		// for (int j = 0; j <= m; ++j)
			// cout << f[i][j] << ' ';
		// cout << endl;
	// }
	// cout << endl;
	// for (int i = 0; i <= n; ++i)
	// {
		// cout << i << " :";
		// for (int j = 0; j <= m; ++j)
			// cout << dp[i][j] << ' ';
		// cout << endl;
	// }
	
	cout << dp[n][m];
	
	return 0;	
}