#include <iostream>
#include <algorithm>
#include <queue>
#include <string.h>
#include <stdio.h>

using namespace std;

struct pos {int x, y, z, l;};

char map[105][105][105];
int l, r, c, ans;
pos s, e;
int dx[] = { -1, 1, 0, 0, 0, 0},
	dy[] = { 0, 0, -1, 1, 0, 0},
	dz[] = { 0, 0, 0, 0, -1, 1};

bool operator == (pos &l, pos &r) {
	return l.x == r.x && l.y == r.y && l.z == r.z;
}

bool can(pos &p) {
	return (p.x >= 0 && p.x < l &&
		p.y >= 0 && p.y < r &&
		p.z >= 0 && p.z < c &&
		map[p.x][p.y][p.z] != '#');
}

int bfs() {
	queue<pos> que;
	que.push(s);
	while (!que.empty()) {
		pos v = que.front();
		que.pop();
		if (map[v.x][v.y][v.z] == '#') continue;
		map[v.x][v.y][v.z] = '#';
		if (v == e) return ans = v.l;
		for (int d = 0; d < 6; ++d) {
			pos c = { v.x + dx[d], v.y + dy[d], v.z + dz[d], v.l + 1};
			if (can(c)) que.push(c);
		}
	}
	return -1;
}

int main() {
	while (cin >> l >> r >> c && (l || r || c)) {
		for (int i = 0; i < l; ++i) {
			for (int j = 0; j < r; ++j) {
				cin >> map[i][j];
				for (int k = 0; k < c; ++k) {
					if (map[i][j][k] == 'S') {
						s.x = i; s.y = j; s.z = k; s.l = 0;
					} else if (map[i][j][k] == 'E') {
						e.x = i; e.y = j; e.z = k;
					}
				}
			}
		}
		if (bfs() != -1) {
			cout << "Escaped in " << ans << " minute(s)." << endl;
		} else {
			cout << "Trapped!" << endl;
		}
	}
	return 0;
}