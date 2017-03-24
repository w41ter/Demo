#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

const int MAX_N = 100 + 1, INF = 0x3f3f3f3f;

struct edge { int to, rev; long long cap; };

vector<edge> G[MAX_N];
int level[MAX_N], iter[MAX_N], n; 
int map[MAX_N][MAX_N];

void add_edge(int from, int to, long long cap) {
	G[from].push_back((edge) { to, G[to].size(), cap });
	G[to].push_back((edge) { from, G[from].size() - 1, cap });
}

void bfs(int s) {
	memset(level, -1, sizeof(level));
	queue<int> que;
	que.push(s);
	level[s] = 0;
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

long long dfs(int v, int t, long long f) {
	if (v == t) return f;
	for (int &i = iter[v]; i < G[v].size(); ++i) {
		edge &e = G[v][i];
		if (e.cap > 0ll && level[e.to] > level[v]) {
			long long d = dfs(e.to, t, min(f, e.cap));
			if (d > 0ll) {
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0ll;
}

long long dinic(int s, int t) {
	long long flow = 0ll; 
	while (true) {
		bfs(s);
		if (level[t] < 0) return flow;
		memset(iter, 0, sizeof(iter));
		long long f = 0ll;
		while ((f = dfs(s, t, INF)) > 0ll) {
			flow += f;
		}
	}
}

int main() {
	while (cin >> n) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cin >> map[i][j];
				if (j <= i) continue;
				add_edge(i, j, map[i][j]);
			}
		}

		long long int ans = dinic(0, n-1);
		for (int k = 0; k < n - 1; ++k) {
			for (int i = 0; i < n; ++i) G[i].clear();
			for (int i = 0; i < n; ++i) {
				for (int j = i + 1; j < n; ++j) {
					add_edge(i, j, map[i][j]);
				}
			}
			//cout << "Find " << k + 1;
			ans = min(ans, dinic(n - 1, k));
			//cout << " and min is " << ans << endl;
		}
		cout << ans << endl;
	}
	return 0;
}