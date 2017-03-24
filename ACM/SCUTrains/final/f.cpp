#include <iostream>
#include <cstring>
#include <string>

using namespace std;

const int INF = 0x3f3f3f3f;

const int VM = 100010;
const int EM = 400010;

struct Edge
{
    int to, frm, nxt, cap;
}edge[EM];

int head[VM],e,n,m,src,des;
int dep[VM], gap[VM];

void edgeInit() {
    e = 0;
    memset(head, -1, sizeof(head));
}

void addEdge(int cu, int cv, int cw)
{
    edge[e].frm = cu;
    edge[e].to = cv;
    edge[e].cap = cw;
    edge[e].nxt = head[cu];
    head[cu] = e++;
    edge[e].frm = cv;
    edge[e].to = cu;
    edge[e].cap = 0;
    edge[e].nxt = head[cv];
    head[cv] = e++;
}

int que[VM];

void BFS()
{
    memset(dep, -1, sizeof(dep));
    memset(gap, 0, sizeof(gap));
    gap[0] = 1;
    int front = 0, rear = 0;
    dep[des] = 0;
    que[rear++] = des;
    int u, v;
    while (front != rear)
    {
        u = que[front++];
        front = front%VM;
        for (int i=head[u]; i!=-1; i=edge[i].nxt)
        {
            v = edge[i].to;
            if (edge[i].cap != 0 || dep[v] != -1)
                continue;
            que[rear++] = v;
            rear = rear % VM;
            ++gap[dep[v] = dep[u] + 1];
        }
    }
}
int cur[VM],stack[VM];
int Sap()       //sap模板
{
    int res = 0;
    BFS();
    int top = 0;
    memcpy(cur, head, sizeof(head));
    int u = src, i;
    while (dep[src] < n)
    {
        if (u == des)
        {
            int temp = INF, inser = n;
            for (i=0; i!=top; ++i)
                if (temp > edge[stack[i]].cap)
                {
                    temp = edge[stack[i]].cap;
                    inser = i;
                }
            for (i=0; i!=top; ++i)
            {
                edge[stack[i]].cap -= temp;
                edge[stack[i]^1].cap += temp;
            }
            res += temp;
            top = inser;
            u = edge[stack[top]].frm;
        }

        if (u != des && gap[dep[u] -1] == 0)
            break;
        for (i = cur[u]; i != -1; i = edge[i].nxt)
            if (edge[i].cap != 0 && dep[u] == dep[edge[i].to] + 1)
                break;

        if (i != -1)
        {
            cur[u] = i;
            stack[top++] = i;
            u = edge[i].to;
        }
        else
        {
            int min = n;
            for (i = head[u]; i != -1; i = edge[i].nxt)
            {
                if (edge[i].cap == 0)
                    continue;
                if (min > dep[edge[i].to])
                {
                    min = dep[edge[i].to];
                    cur[u] = i;
                }
            }
            --gap[dep[u]];
            ++gap[dep[u] = min + 1];
            if (u != src)
                u = edge[stack[--top]].frm;
        }
    }
    return res;
}


int main() {
    std::ios::sync_with_stdio(false);
    
    int t;
    cin >> t;
    while (t--) {

        int x, y, Min = INF, Max = -INF;
        cin >> n >> m;
        for (int i = 1; i <= n; ++i)       //找出起点src 终点des
        {
            cin >> x >> y;
            if (x <= Min)
            {
                src = i;
                Min = x;
            }
            if (x >= Max)
            {
                des = i;
                Max = x;
            }
        }

        edgeInit();
        int u, v, c;
        for (int i = 0; i != m; ++i)
        {
            cin >> u >> v >> c;
            addEdge(u, v, c);
            addEdge(v, u, c);
        }  
    
        cout << Sap() << endl;
    }
    return 0;
}