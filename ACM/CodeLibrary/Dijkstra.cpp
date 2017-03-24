#include <iostream>
#include <cstring>

using namespace std;

int dist[100];
int visit[100];
int w[100][100];
const int INF = 0XFFFFF;

int min(int l, int r)
{
	if (l < r)
		return l;
	else
		return r;
}

void Dijkstra(int n, int b)
{
	memset(visit, 0, sizeof(visit));
	for (int i = 0; i <= n; i++) dist[i] = INF;
	dist[b] = 0;
	for (int i = 1; i <= n; i++)
	{
		int x, m = INF;
		for (int j = 1; j <= n; j++)
			if (!visit[j] && dist[j] < m)
				m = dist[x = j];
		
		visit[x] = 1;
		for (int j = 1; j <= n; j++)
			if (w[x][j] != -1) 
				dist[j] = min(dist[j], dist[x] + w[x][j]);
	}
}

int main()
{
	int n, b, e, l, r, v, s;
	cin >> n >> s >> b >> e;
	
	memset(w, -1, sizeof(w));
	
	for (int i = 0; i < s; i++)
	{
		cin >> l >> r >> v;
		w[l][r] = v;
		w[r][l] = v;
	}
	
	Dijkstra(n, b);
	cout << "Distance is : " << dist[e] << endl;

	return 0;
}