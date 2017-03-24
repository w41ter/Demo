#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <cstdio>

using namespace std;

struct pii { int first, second;};

char map[20][20];
int m, n, visit[20][20];
vector<pii> vec;
int dx[] = { -1, 1, 0, 0}, dy[] = { 0, 0, 1, -1};

inline bool can(int x, int y) {
	if (0 <= x && x < n && 0 <= y && y < m &&
		map[x][y] == '#' && !visit[x][y]) return true;
	else return false;
}

inline bool is_all_visit() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (map[i][j] == '#' && !visit[i][j]) return false;
		}
	}
	return true;
}

int bfs(pii &a, pii &b) {
	queue<pii> que;
	que.push(a); que.push(b);
	memset(visit, 0, sizeof(visit));
	visit[a.first][a.second] = visit[b.first][b.second] = 1;
	int ans = -1;
	while (!que.empty()) {
		pii p = que.front(); que.pop();
		if (visit[p.first][p.second] > ans) ans = visit[p.first][p.second];
		for (int i = 0; i < 4; ++i) {
			pii tmp = { p.first + dx[i], p.second + dy[i] };
			if (can(tmp.first, tmp.second)) {
				que.push(tmp);
				visit[tmp.first][tmp.second] = visit[p.first][p.second] + 1;
			}
		}
	}
	return ans - 1;
}

int solve() {
	int ans = 0x3f3f3f;
	for (int i = 0; i < vec.size(); ++i) {
		for (int j = i; j < vec.size(); ++j) {
			int tmp = bfs(vec[i], vec[j]);
			if (is_all_visit()) ans = min(ans, tmp);
		}
	}
	return ans == 0x3f3f3f ? -1 : ans;
}

int main() {
	//freopen("test.txt","r",stdin);
    //freopen("b.txt", "w", stdout);
	vec.resize(205);
	int t, _case = 0;
	scanf("%d", &t);
	while (++_case <= t) {
		vec.clear();
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i) { 
			scanf("%s", &map[i]);
			for (int j = 0; j < m; ++j) {
				if (map[i][j] == '#')
					vec.push_back((pii) {i, j});
			}
		}

		printf("Case %d: %d\n", _case, solve());
	}
	return 0;
}