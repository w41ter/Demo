#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cstdio>
#include<sstream>
#include<string>
#include<cmath>
using namespace std;

const int MAXN = 20100;
const int MAXM = 900000;
const int INF = 0x3f3f3f3f;

struct Edge
{
    int from, to, cap, next;
};

Edge edge[MAXM];
int level[MAXN];
int map[150][150];
int head[MAXN];
int src, des, cnt = 0;

void addedge( int from, int to, int cap )
{
    edge[cnt].from = from;
    edge[cnt].to = to;
    edge[cnt].cap = cap;
    edge[cnt].next = head[from];
    head[from] = cnt++;

    swap( from, to );

    edge[cnt].from = from;
    edge[cnt].to = to;
    edge[cnt].cap = 0;
    edge[cnt].next = head[from];
    head[from] = cnt++;
}

int bfs( )
{
    memset( level, -1, sizeof level );
    queue<int> q;
    while (!q.empty( ))
        q.pop( );
    level[src] = 0;
    q.push( src );

    while (!q.empty( ))
    {
        int u = q.front( );
        q.pop( );
        for (int i = head[u]; i != -1; i = edge[i].next)
        {
            int v = edge[i].to;
            if (edge[i].cap&&level[v] == -1)
            {
                level[v] = level[u] + 1;
                q.push( v );
            }
        }
    }
    return level[des] != -1;
}

int dfs( int u, int f )
{
    if (u == des) return f;

    int tem;
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if (edge[i].cap&&level[v] == level[u] + 1)
        {
            tem = dfs( v, min( f, edge[i].cap ) );
            if (tem > 0)
            {
                edge[i].cap -= tem;
                edge[i ^ 1].cap += tem;
                return tem;
            }
        }
    }
    level[u] = -1;
    return 0;
}


int Dinic( )
{
    int ans = 0, tem;

    while (bfs( ))
    {
        while (tem = dfs( src, INF ))
        {
            ans += tem;
        }
    }
    return ans;
}

int main( )
{
    int kase, m, n;
    cin >> kase;
    src = 0; des = 20005;
    
    while (kase--)
    {
        cin >> n>>m;
        memset( head, -1, sizeof head );
        cnt = 0;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                cin >> map[i][j];
                if (map[i][j])
                {
                    if ((i + j) % 2 == 1)
                        addedge( src, (i - 1) *100 + j, 1 );
                    else
                        addedge( (i - 1) * 100 + j, des, 1 );
                }
            }
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (!map[i][j])  continue;

                if (i+1<=n&&map[i+1][j])
                {
                    addedge( (i - 1) * 100 + j, i * 100 + j, 1 );
                }
                if (j + 1 <= m&&map[i][j+1])
                {
                    addedge( (i - 1) * 100 + j, (i - 1) * 100 + j + 1, 1 );
                }
                if (i - 1 >= 1 && map[i-1][j])
                {
                    addedge( (i - 1) * 100 + j, (i - 2) * 100 + j , 1 );
                }
                if (j - 1 >= 1 && map[i][j-1])
                {
                    addedge( (i - 1) * 100 + j, (i - 1) * 100 + j - 1, 1 );
                }
            }
        }
        cout << Dinic() * 2 << endl;
    }
    return 0;
}