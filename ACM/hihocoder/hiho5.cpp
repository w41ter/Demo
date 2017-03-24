#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

//#define LOACLFILE 
const int N = 210;
int dp[N][N], reworad[N][N], ans;

int main()
{
	std::ios::sync_with_stdio(false);
	
	#ifdef LOACLFILE
	std::ifstream in("1.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
	#endif

	int n = 0;
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= i; ++j)
			cin >> reworad[i][j];
	}
	
	// for (int i = 0; i <= n; ++i)
	// {
		// for (int j = 0; j <= n; ++j)
			// cout << reworad[i][j] << ' ';
		// cout << endl;
	// }
	
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= i; ++j)
		{
			dp[i][j] = max(dp[i-1][j-1], dp[i-1][j]) + reworad[i][j];
		}
	}
	
	// cout << endl << endl;
	
	// for (int i = 0; i <= n; ++i)
	// {
		// for (int j = 0; j <= n; ++j)
			// cout << dp[i][j] << ' ';
		// cout << endl;
	// }
		
		
	for (int i = 1; i <= n; i++)
		if (ans < dp[n][i]) ans = dp[n][i];
	cout << ans;
	
	return 0;
}