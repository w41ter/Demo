#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

struct edge { int u, v, cost;};

const int MAX_R = 50000 + 10;
const int MAX_N = 10000 + 10;

int N, M, R;
int parent[MAX_N * 2];
edge E[MAX_R];

bool cmp(const edge &l, const edge &r) { return l.cost < r.cost; }

void init(int n) { for (int i = 0; i < n; ++i) parent[i] = i;}

int find(int v) { return parent[v] = parent[v] == v ? v : find(parent[v]);}

void unite(int v, int u) {
	int x = find(v), y = find(u);
	if (x != y) parent[y] = x;
}

bool same(int v, int u) { return find(v) == find(u); }

int kruskal() {
	sort(E, E + R, cmp);
	init(N + M);
	int res = 0;
	for (int i = 0; i < R; ++i) {
		edge &e = E[i];
		if (!same(e.v, e.u)) {
			unite(e.u, e.v);
			res += e.cost;
		}
	}
	return res;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d", &N, &M, &R);
		for (int i = 0; i < R; ++i) {
			int x, y, c;
			scanf("%d%d%d", &x, &y, &c);
			E[i] = {x, y + N, -c};
		}
		printf("%d\n", 10000 * (N + M) + kruskal());
	}
	return 0;
}