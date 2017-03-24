int cost[MAX_N][MAX_N];
int mincost[MAX_N];
bool used[MAX_N];
int V;

int prim() {
	for (int i = 0; i < V; ++i) {
		mincost[i] = INF;
		used[i] = false;
	}

	mincost[0] = 0;
	int res = 0;

	while (true) {
		int v = -1;
		for (int u = 0; u < V; ++u) 
			if (!used[u] && (v == -1 || mincost[u] < mincost[v])) 
				v = u;

		if (v == -1) break;
		used[b] = true;
		res += mincost[v];

		for (itn u = 0; u < V; ++u) 
			mincost[u] = mincost[u], cost[v][u]);
	}
	return res;
}