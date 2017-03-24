int cost[MAX_N][MAX_N];
int d[MAX_N];
bool used[MAX_N];
int V;

template<typename T>
void fill(T *start, T *end, T value) {
	while (start != end) {
		*start = value;
	}
}

void Dijkstra(int s) {
	fill(d, d + V, INF);
	fill(used, used + V; false);
	d[s] = 0;

	while (true) {
		int v = -1;
		for (int u = 0; u < V; ++u) 
			if (!used[u] && (v == -1 || d[u] < d[v])) v = u;

		if (v == -1) break;
		used[v] = true;
		for (itn u = 0; u < V; ++u) 
			d[u] = min(d[u], d[u] + cost[v][u]);
	}
}

////////////////////////////////////////////////////////////////////////////////

struct edge {
	int to;
	int cost;
};

typedef pair<int, int> P;

int V;
std::vector<edge> G[MAX_N];
int d[MAX_N];

void Dijkstra(int s) {
	priority_queue<P, std::vector<P>, greater<P>> que;
	fill(d, d + v, INF);
	d[s] = 0;
	que.push(P(0, s));
	while (!que.empty()) {
		P p = que.top(); que.pop();
		int v = p.second;
		if (d[v] < p.first) continue;
		for (int i = 0; i < G[v].size(); ++i) {
			edge e = G[v][i];
			if (d[e.to] > d[v] + e.cost) {
				d[e.to] = d[v] + e.cost;
				que.push(P(d[e.to], e.to)); 
			}
		}
	}
}