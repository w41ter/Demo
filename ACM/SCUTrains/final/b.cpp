#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <set>

//#define LOACLFILE 

using namespace std;
const int MAXN = 100 + 5;
std::vector<int> tree[MAXN];
std::map<int, map<int, int>> room;
int N, T, st, treasure[MAXN], vis[MAXN];
int dp[MAXN][510];

bool find_dfs(int n, int t) {
	//cout << " n = " << n << " t = " << t << endl;
	if (t < 0) return false;
	if (n == N) {
		st = t;
		return true;	
	} 

	vis[n] = 1;
	for (int i = 0; i < tree[n].size(); ++i) {
		int p = tree[n][i];
		//cout << "point " << p << endl;
		if (vis[p]) continue;
		if (find_dfs(p, t - room[n][p])) {
			room[n][p] = 0;
			room[p][n] = 0;
			return true;
		}
	}
	return false;
}

void dfs(int n) {
	vis[n] = 1;
	for (int i = 0; i <= st; ++i) dp[n][i] = treasure[n];

	for (int i = 0; i < tree[n].size(); ++i) {
		int p = tree[n][i];
		if (vis[p]) continue;
		dfs(p);
		int cost = room[n][p] * 2;
		for (int j = st; j >= cost; --j) {
			for (int k = 0; k <= j - cost; ++k) {
				dp[n][j] = max(dp[n][j], dp[p][k] + dp[n][j - cost - k]);
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	
	#ifdef LOACLFILE
	std::ifstream in("1.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
	#endif

    while (cin >> N >> T) {
    	room.clear();
    	memset(vis, 0, sizeof(vis));
    	memset(treasure, 0, sizeof(treasure));
    	memset(dp, 0, sizeof(dp));
    	for (int i = 0; i < MAXN; ++i) tree[i].clear();
    		
    	int a, b, c;
		for (int i = 0; i < N - 1; ++i) {
			cin >> a >> b >> c;
			tree[a].push_back(b);
			tree[b].push_back(a);
			room[a][b] = room[b][a] = c;
		}
		for (int i = 1; i <= N; ++i)
		{
			cin >> c;
			treasure[i] = c;
		}

		//cout << N << T << endl;
		if (!find_dfs(1, T)) {
			cout << "Human beings die in pursuit of wealth, and birds die in pursuit of food!" << endl;
			continue;
		}	// 找到最短路

		memset(vis, 0, sizeof(vis));
		dfs(1);
		cout << dp[1][st] << endl;
	
    }
	return 0;
}