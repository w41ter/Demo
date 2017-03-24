#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

//#define LOACLFILE 

const int N = 5e4 + 10;
vector<int> point[N];
int vis[N], n, k, a, b, ans;
int dp[N][510];

void dfs(int t) 
{
	//cout << "begin dfs : " <<  t << endl;
	vis[t] = 1;
	memset(dp[t], 0, sizeof(dp[t]));
	dp[t][0] = 1;
	for (int i = 0; i < point[t].size(); ++i) {
		int child = point[t][i];
		if (vis[child]) continue;
		
		dfs(child);
		for (int j = 0; j < k; ++j) ans += dp[child][j]*dp[t][k-j-1];
		for (int j = 1; j <= k; ++j) dp[t][j] += dp[child][j-1];
		//cout << "\tnow dp[t][j] = " << dp[t][k] << endl;
	}
	//cout << "now dp[t][m] = " << dp[t][k] << " ans is : " << ans << endl;
	//cout << "end dfs :" << t << endl;
}

int main()
{
	std::ios::sync_with_stdio(false);
	
	#ifdef LOACLFILE
	std::ifstream in("1.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
	#endif

	while (cin >> n >> k)
	{
		for (int i = 1; i < n; ++i) {
			cin >> a >> b;
			point[a].push_back(b);
			point[b].push_back(a);
		}
		//cout << n << " " << k << endl;
		//continue;
		//for (int i = 1; i <= n; ++i)
		//	cout << i << " length is " << point[i].size()  << endl;
		
		ans = 0;
		dfs(1);
		cout << ans << endl;
		for (int i = 1; i <= n; ++i)
			point[i].clear(), vis[i] = 0;
	}
	
	
	// for (int i = 0; i <= n; ++i){
		// cout << i << "has point " << point[i].size() << endl;
	// }
	

	return 0;
}