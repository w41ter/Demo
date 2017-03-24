#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

const int MAX_N = 20 + 5;
char M[MAX_N][MAX_N];
int vis[MAX_N][MAX_N];
int x, y, W, H;
int dx[] = { -1, 1, 0, 0}, dy[] = { 0, 0, -1, 1};

int bfs() {
	queue<pii> que;
	que.push(pii(x, y));
	int ans = 0;
	while (!que.empty()) {
		pii p = que.front(); que.pop();
		int i = p.first, j = p.second;
		ans++;
		for (int k = 0; k < 4; ++k) {
			int i1 = i + dx[k], j1 = j + dy[k];
			if (i1 < 0 || i1 >= H) continue;
			if (j1 < 0 || j1 >= W) continue;
			if (M[i1][j1] == '.' && !vis[i1][j1]) {
				vis[i1][j1] = 1;
				que.push(pii(i1, j1));
			}
		}
	}
	return ans;
}

int main() {
	while (true) {
		scanf("%d%d", &W, &H);
		if (W == 0 && H == 0) return 0;
		for (int i = 0; i < H; ++i) {
			scanf("%s", M[i]);
			for (int j = 0; j < W; ++j) {
				vis[i][j] = 0;
				if (M[i][j] == '@') {
					x = i;
					y = j;
				}
			}
		}
		printf("%d\n", bfs());
	}

	return 0;
}