#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <queue>
#include <vector>
#include <string.h>

using namespace std;

template<int N,int M>  
struct Graph  
{  
    int top;  
    struct Vertex{  
        int head;  
    }V[N];  
    struct Edge{  
        int to, next, cost;  
    }E[M];  
    void init(){  
        memset(V,-1,sizeof(V));  
        top = 0;  
    }  
    void add_edge(int u,int v,int w){  
        E[top].to = v;  
        E[top].cost = w;  
        E[top].next = V[u].head;  
        V[u].head = top++;  
    }  
};  
  
Graph<50005,150005> graph;
const int MAX_N = 5e4 + 5;  
const int INF = 0xfffffff;
int n, _min, _max, inq[MAX_N], d[MAX_N];

bool bellman_ford() {
	queue<int> que;
	memset(inq, 0, sizeof(inq));
	for (int i = _min; i <= _max; ++i) d[i] = INF;
	d[_max] = 0; inq[_max] = true;
	que.push(_max);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		inq[u] = false;
		for (int i = graph.V[u].head; i != -1; i = graph.E[i].next) {
			int to = graph.E[i].to, cost = graph.E[i].cost;
			if (d[u] + cost < d[to]) {
				d[to] = d[u] + cost;
				if (!inq[to]) { que.push(to); inq[to] = true; }
			}
		}
	}
	return true;
}

int main() {
	while (~scanf("%d", &n)) {
		graph.init();
		_min = INF;
		for (int i = 0; i < n; ++i) {
			int u, v, c;
			scanf("%d%d%d", &u, &v, &c);
			graph.add_edge(v+1, u, -c);
			_min = min(_min, u);
			_max = max(_max, v+1);
		}
		for (int i = _min; i <= _max; ++i) {
			graph.add_edge(i, i+1, 1);
			graph.add_edge(i+1, i, 0);
		}
		bellman_ford();
		//for (int i = _min; i <= _max; ++i)
		printf("%d\n", -d[_min]);
	}
	return 0;
}