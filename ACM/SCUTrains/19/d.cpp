#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

//#define LOACLFILE 

struct Edge
{
	int to;
	int cap;
};

const int VM=1010;
const int EM=200010;
const int INF=0x3f3f3f3f;
const int N = 2000;

vector<Edge> edge;
vector<int> G[EM];

int dis[EM], cur[EM], cf;

int n, f, d;

void addedge(int from, int to, int cap)
{
	edge.push_back({to, cap});
	edge.push_back({from, 0});
	int id = edge.size();
	G[from].push_back(id-2);
	G[to].push_back(id-1);
}

int src, des;

bool bfs()
{
	memset(dis, 0, sizeof(dis));
	queue<int> Q;
	Q.push(src);
	dis[src] = 1;
	while (!Q.empty())
	{
		int x = Q.front(); Q.pop();
		if (x == des) return true;
		for (int i = 0; i < G[x].size(); ++i)
		{
			Edge &e = edge[G[x][i]];
			if (!dis[e.to] && e.cap > 0)
			{
				dis[e.to] = dis[x] + 1;
				//dis[e.to] = x;
				Q.push(e.to);
			}
		}
	}
	return false;
}

int dfs(int x, int a)
{
	if (x == des || a == 0) return a;
	int flow = 0, f;
	for (int &i = cur[x]; i < G[x].size(); ++i)
	{
		Edge &e = edge[G[x][i]];
		if (dis[x] + 1 == dis[e.to] && (f = dfs(e.to, min(a, e.cap))) > 0)
		{
			e.cap -= f;
			edge[G[x][i]^1].cap += f;
			flow += f;
			a -= f;
			if (a == 0) break;
		}
	}
	return flow;
}

int max_flow()
{
	int flow = 0;
	while (bfs())
	{
		memset(cur, 0, sizeof(cur));
		flow += dfs(src, INF);
	}
	return flow;
}

int main()
{
	std::ios::sync_with_stdio(false);
	
	#ifdef LOACLFILE
	std::ifstream in("1.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
	#endif

	while (cin >> n >> f >> d)
	{
		int food, drank;
		
		src = 0, des = f + 2 * n + d + 1;
		
		edge.clear();
		for(int i = 0; i < des + 2; i++) G[i].clear();
		
		for (int i = 1; i <= f; ++i)
		{
			cin >> food;
			addedge(src, i, food);
		}
		for (int i = f + 2 * n + 1; i <= f + 2 * n + d; ++i)
		{
			cin >> drank;
			addedge(i, des, drank);
		}
		
		char str[220];
		for (int i = 1; i <= n; ++i)
		{
			cin >> str;
			for (int j = 0; j < f; ++j)
				if (str[j] == 'Y') addedge(j + 1, f + i, 1);
		}
		for (int i = 1; i <= n; ++i)
		{
			cin >> str;
			for (int j = 0; j < d; ++j)
				if (str[j] == 'Y') addedge(f + n + i, f + 2 * n + j + 1, 1);
		}
		
		for (int i = f + 1; i <= f + n; i++)
			addedge(i, i + n, 1);
		
		cout << max_flow() << endl;
	}
	
	return 0;
}