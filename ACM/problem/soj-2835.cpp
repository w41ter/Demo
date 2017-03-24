#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>

using namespace std;

struct edge { int to, cap, rev; };

const int MAX_N = 20100;
const int MAX_V = 900000;
const int INF = 0x3f3f3f3f;

vector<edge> G[MAX_N];
bool used[MAX_N];
int map[150][150];

inline void add_edge(int from, int to, int cap) {
	G[from].push_back((edge){to, cap, G[to].size()});
	G[to].push_back((edge){from, 0, G[from].size() - 1});
}

int dfs(int v, int t, int f) {
	if (v == t) return f;
	used[v] = true;
	for (int i = 0; i < G[v].size(); ++i) {
		edge &e = G[v][i];
		if (!used[e.to] && e.cap > 0) {
			int d = dfs(e.to, t, min(f, e.cap));
			if (d > 0) {
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

int max_flow(int s, int t) {
	int flow = 0;
	while (true) {
		memset(used, 0, sizeof(used));
		int f = dfs(s, t, INF);
		if (f == 0) return flow;
		flow += f;
	}
}

int main() {
	int t;
	scanf("%d", &t);
	for (int i = 0; i < MAX_N; ++i) G[i].resize(100);
	int src = 0, des = MAX_N - 1;
	while (t--) {
		for (int i = 0; i < MAX_N; ++i) G[i].clear();

		int n, m;
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &map[i][j]);
				if (map[i][j]) {
					if ((i + j) % 2 == 1) 
						add_edge(0, (i - 1) * 100 + j, 1);
					else 
						add_edge((i - 1) * 100 + j, des, 1);
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (!map[i][j]) continue;

				if (i+1 <= n && map[i+1][j])
					add_edge((i - 1) * 100 + j, i * 100 + j, 1);

				if (j + 1 <= m && map[i][j+1]) 
					add_edge((i - 1) * 100 + j, (i - 1) * 100 + j + 1, 1);

				if (i - 1 >= 1 && map[i-1][j])
					add_edge((i - 1) * 100 + j, (i - 2) * 100 + j , 1);

				if (j - 1 >= 1 && map[i][j-1])
					add_edge((i - 1) * 100 + j, (i - 1) * 100 + j - 1, 1);
			}
		}
		printf("%d\n", max_flow(src, des) << 1);
	}
	return 0;
}