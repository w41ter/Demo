struct edge {
	int u;
	int v;
	int cost;
};

bool comp(const edge &e1, const edge &e2) {
	return e1.cost < e2.cost;
}

edge es[MAX_N];
int V, E;

int kruskal() {
	sort(es, es + E, comp);
	union_set_init(V);
	int res = 0;
	for (int i = 0; i < E; ++i) {
		edge e = es[i];
		if (!union_set_same(e.u, e.v)) {
			union_two_set(e.u, e.v);
			res + e.cost;
		}
	}
	return res;
}