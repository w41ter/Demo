#include <iostream>
#include <algorithm>
#include <queue>
#include <string.h>
#include <stdio.h>

using namespace std;

struct pos {int x, y, z, l;};

char str[31];
int l, r, c, ans, map[30][30];
pos s, e;
int dx[] = { -1, 1, 0, 0, 0, 0},
	dy[] = { 0, 0, -1, 1, 0, 0},
	dz[] = { 0, 0, 0, 0, -1, 1};

bool operator == (pos &l, pos &r) {
	return l.x == r.x && l.y == r.y && l.z == r.z;
}

bool is_one(pos &p) {
	int carry = 1;
	for (int i = 0; i < p.z; ++i) {
		carry <<= 1;
	}
	return carry & map[p.x][p.y];
}

void set(pos &p) {
	int carry = 1;
	for (int i = 0; i < p.z; ++i) {
		carry <<= 1;
	}
	map[p.x][p.y] &= ~carry;
}

bool can(pos &p) {
	return (p.x >= 0 && p.x < l &&
		p.y >= 0 && p.y < r &&
		p.z >= 0 && p.z < c &&
		is_one(p));
}

int bfs() {
	queue<pos> que;
	que.push(s);
	while (!que.empty()) {
		pos v = que.front();
		que.pop();
		if (!is_one(v)) continue;
		set(v);
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
		memset(map, 0, sizeof(map));
		for (int i = 0; i < l; ++i) {
			for (int j = 0; j < r; ++j) {
				cin >> str;
				for (int k = 0; k < c; ++k) {
					if (str[k] == 'S') {
						s.x = i; s.y = j; s.z = k; s.l = 0;
					} else if (str[k] == 'E') {
						e.x = i; e.y = j; e.z = k;
					}
				}
				int carry = 1;
				for (int k = 0; k < c; ++k) {
					if (str[k] != '#')
						map[i][j] |= carry;
					carry <<= 1;
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