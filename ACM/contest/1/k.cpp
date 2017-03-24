#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct pii { int first, second, parent;};

vector<pii> vec;
int map[5][5];
int dx[] = { 1, -1, 0, 0}, dy[] = { 0, 0, 1, -1};

void output(int pos) {
	if (pos == 0) {
		cout << "(0, 0)" << endl;
	} else {
		pii p = vec[pos];
		output(p.parent);
		cout << '(' << p.first << ", " << p.second << ')' << endl;
	}
}

bool can(pii p) {
	if (0 <= p.first && p.first < 5 &&
		0 <= p.second && p.second < 5 &&
		map[p.first][p.second] == 0)
		return true;
	else return false;
}

int bfs() {
	queue<int> que;
	pii head = {0, 0, -1};
	vec.push_back(head);
	que.push(0);
	while (!que.empty()) {
		int pos = que.front(); que.pop();
		pii p = vec[pos];
		if (p.first == 4 && p.second == 4) return pos;
		for (int i = 0; i < 4; ++i) {
			pii tmp = { p.first + dx[i], p.second + dy[i], pos };
			if (can(tmp)) {
				tmp.parent = pos;
				vec.push_back(tmp);
				que.push(vec.size() - 1);
				map[tmp.first][tmp.second] = 1;
			}
		}
	}
}
int main() {
	vec.resize(30);
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			cin >> map[i][j];
		}
	}

	int pos = bfs();
	output(pos);
	return 0;
}