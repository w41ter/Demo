#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>
#include <queue>

using namespace std;

struct edge { int to, cap, rev; };

const int MAX_N = 20100;
const int INF = 0x3f3f3f3f;

vector<edge> G[MAX_N];
int level[MAX_N], iter[MAX_N];
int map[150][150];

inline void add_edge(int from, int to, int cap) {
	G[from].push_back((edge){to, cap, G[to].size()});
	G[to].push_back((edge){from, 0, G[from].size() - 1});
}

void bfs(int s) {
	memset(level, -1, sizeof(level));
	queue<int> que;

	level[s] = 0;
	que.push(s);
	while (!que.empty()) {
		int v = que.front(); que.pop();
		for (int i = 0; i < G[v].size(); ++i) {
			edge &e = G[v][i];
			if (e.cap > 0 && level[e.to] < 0) {
				level[e.to] = level[v] + 1;
				que.push(e.to);
			}
		}
	}
}

int dfs(int v, int t, int f) {
	if (v == t) return f;
	for (int &i = iter[v]; i < G[v].size(); ++i) {
		edge &e = G[v][i];
		if (e.cap > 0 && level[e.to] > level[v]) {
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
		bfs(s);
		if (level[t] < 0) return flow;
		memset(iter, 0, sizeof(iter));
		int f;
		while ((f = dfs(s, t, INF)) > 0) {
			flow += f;
		}
	}
}

int main() {
	int t;
	scanf("%d", &t);

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
				if (!map[i][j] || ((i + j) % 2 == 0)) continue;

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