#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

#define LOACLFILE 

const int N = 1e2 + 10;
vector<int> point[N];
int vi[N], vis[N], n, m, a, b;
int dp[N][N];

void dfs(int t) 
{
	//cout << "begin dfs : " <<  t << endl;
	vis[t] = 1;
	dp[t][1] = vi[t];
	for (int i = 0; i < point[t].size(); ++i) {
		if (vis[point[t][i]]) continue;
		//cout << "\tChild node : " << point[t][i] << endl;
		dfs(point[t][i]);
		for (int j = m; j > 1; --j) {
			for (int cm = 1; cm < j; ++cm) {
				dp[t][j] = max(dp[t][j], dp[t][j - cm] + dp[point[t][i]][cm]);
			}
		}
		//cout << "\tnow dp[t][j] = " << dp[t][m] << endl;
	}
	//cout << "now dp[t][m] = " << dp[t][m] << endl;
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

	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> a;
		vi[i] = a;
	}
	for (int i = 0; i <= n - 2; ++i) {
		cin >> a >> b;
		point[a].push_back(b);
		point[b].push_back(a);
	}
	
	// for (int i = 0; i <= n; ++i){
		// cout << i << "has point " << point[i].size() << endl;
	// }
	
	dfs(1);
	cout << dp[1][m];
	return 0;
}