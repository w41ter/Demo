#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int map[6][6] = {
    {0, 2, 10, 5, 3, -1},
    {-1, 0, 12, -1, -1, 10},
    {-1, -1, 0, -1, 7, -1},
    {2, -1, -1, 0, 2, -1},
    {4, -1, -1, 1, 0, -1},
    {3, -1, 1, -1, 2, 0}
};

int get_min(int dist[], bool visited[], int v) {
    int min = 1000;
    int index = -1;
    for (int i = 0; i < 6; ++i) {
        if (!visited[i] && dist[i] != -1 && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

int dj(int from, int to, vector<vector<int> > & cost, int parent[]) 
{
    int dist[6] = { -1 };
    bool visit[6] = { false };

    for (int i = 0; i < 6; ++i) {
        dist[i] = cost[from][i];
        visit[i] = false;
        parent[i] = -1;
    }

    parent[from] = -1;
    dist[from] = 0;
    visit[from] = true;
    for (int i = 0; i < 6; ++i) {
        int u = get_min(dist, visit, from);
        if (u == -1) break;
        visit[u] = true;    
        for (int j = 0; j < 6; ++j) {
            if (!visit[j] && map[u][j] != -1 && (dist[j] == -1 || dist[u] > dist[u] + map[u][j])) {
                dist[j] = dist[u] + map[u][j];
                parent[j] = u;
            }
        }
    }
    return dist[to];
}

int main() 
{
    int x, y;
    while (cin >> x >> y) {
        x--; y--;
        vector<vector<int> > edges(6, vector<int>(6, -1));
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                edges[i][j] = (i == y || j == y) ? -1 : map[i][j];
            }
        }

        int parent[6] = { -1 };
        int dist = dj(4, x, edges, parent);
        if (dist != -1) {
            cout << dist << endl;
            vector<int> result;
            int idx = x;
            while (idx != -1) {
                result.push_back(idx + 1);
                idx = parent[idx];
            }
            result.push_back(5);
            reverse(result.begin(), result.end());
            cout << '[';
            for (int i = 0; i < result.size(); ++i) {
                if (i > 0) cout << ", ";
                cout << result[i];
            }
            cout << ']' << endl;
        }
        else 
            cout << 1000 << endl;
    }
    return 0;
}