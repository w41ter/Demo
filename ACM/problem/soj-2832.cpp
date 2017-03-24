#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
//#include <stack>

using namespace std;

template<int VEC, int EDG>
struct Graph {
	int total = 0;
	int head[VEC];
	struct {
		int from, to, cost, next;
	} edge[EDG];

	void init(int n = VEC) {
		total = 0;
		memset(head, -1, sizeof(int) * n);
	}

	void push(int u, int v, int c) {
		edge[total].from = u;
		edge[total].to = v;
		edge[total].cost = c;
		edge[total].next = head[u];
		head[u] = total++;
	}

	const int end() const { return -1; }

	int next(int i) { return edge[i].next; }
};

template <int TOTAL>
struct Stack {
	int stack[TOTAL];
	int top = 0;
	void init() { top = 0; }
	void push(int v) { stack[++top] = v;}
	int pop() { return stack[top--]; }
	bool empty() { return top == 0; }
};

const int INF = 0x3ffffff;
const int MAX_N = 100005;
Graph<MAX_N, MAX_N> graph;
Stack<100005> stack;
int dfn[MAX_N], low[MAX_N], sccno[MAX_N], min_cost[MAX_N], indeg[MAX_N];
int n, m, colok, scc_cnt, w[MAX_N];

void tarjan(int u) {
	dfn[u] = low[u] = ++colok;
	stack.push(u);
	for (int i = graph.head[u]; i != graph.end(); i = graph.next(i)) {
		int v = graph.edge[i].to;
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[v], low[u]);
		} else if (!sccno[v]) {
			low[u] = min(dfn[v], low[u]);
		}
	}
	if (dfn[u] == low[u]) {
		scc_cnt++;
		while (true) {
			int j = stack.pop();
			sccno[j] = scc_cnt;
			
			min_cost[scc_cnt] = min(min_cost[scc_cnt], w[j]);
			if (u == j) break;
		} 
	}
}

int solve() {
	for (int i = 1; i <= n; ++i) {
		if (!dfn[i]) tarjan(i);
	}

	for (int i = 1; i <= scc_cnt; ++i) 
		indeg[i] = 0;
	for (int i = 0; i < m; ++i) {
		int a = graph.edge[i].from;
		int b = graph.edge[i].to;
		if (sccno[a] != sccno[b])
			indeg[sccno[b]]++;
	}
	int ans = 0;
	for (int i = 1; i <= scc_cnt; ++i) 
		if (!indeg[i]) ans += min_cost[i];
	return ans;
}

int main() {
	while (scanf("%d%d", &n, &m) == 2) {
		colok = scc_cnt = 0;
		stack.init();
		graph.init(n+1);
		fill(min_cost, min_cost + n + 1, INF);
		memset(dfn, 0, (n + 1) * sizeof(dfn[0]));
		memset(low, 0, (n + 1) * sizeof(low[0]));
		memset(sccno, 0, (n + 1) * sizeof(sccno[0]));

		int a, b;
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", &a, &b);
			w[a] = b;
		}
		for (int i = 0; i < m; ++i) {
			scanf("%d%d", &a, &b);
			graph.push(a, b, 0);
		}

		printf("%d\n", solve());
	}
	return 0;
}