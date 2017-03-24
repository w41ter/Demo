#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <stdio.h>

using namespace std;

typedef pair<int, int> pii;

struct edge { int to; int cost; };

const int INF = 1e9 + 7;
const int MAX_N = 5000 + 5;
int N, R;
int dist[MAX_N], dist2[MAX_N];
vector<edge> G[MAX_N];

void solve() {
	priority_queue<pii, vector<pii>, greater<pii> > que;

	fill(dist, dist + N, INF);
	fill(dist2, dist2 + N, INF);

	dist[0] = 0;
	que.push(pii(0, 0));
	while (!que.empty()) {
		pii point = que.top(); que.pop();
		int v = point.second;
		if (dist2[v] < point.first) continue;
		for (int i = 0; i < G[v].size(); ++i) {
			edge &e = G[v][i];
			int d2 = point.first + e.cost;
			if (dist[e.to] > d2) {
				swap(dist[e.to], d2);
				que.push(pii(dist[e.to], e.to));
			}
			if (dist2[e.to] > d2 && dist[e.to] < d2) {
				dist2[e.to] = d2;
				que.push(pii(dist2[e.to], e.to));
			}
		}
	}
	printf("%d\n", dist2[N-1]);
}

int main() {
	scanf("%d%d", &N, &R);
	for (int K = 0; K < R; ++K) {
		int i, j, c;
		scanf("%d%d%d", &i, &j, &c);
		i--; j--;
		G[i].push_back({j, c});
		G[j].push_back({i, c});
	}

	solve();
	return 0;
}