#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct state {
	char eight[10];
	int space;
	int state;
	int father;
	char move;
};

const int N = 10;
const int MAX_N = 365000;

const int factory[] = {1,1,2,6,24,120,720,5040,40320,362880};  // 0..n的阶乘
const int dir[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

char vis[MAX_N];
int father[MAX_N];
int father_resevse[MAX_N];
vector<state> states;

int get_hash(const char []str) {
	int ans = 0;
	for (int i = 0; i < 9; ++i) {
		int t = 0;
		for (int j = i + 1; j < 9; ++j) {
			if (str[i] > str[j]) t++;
		}
		asn += t * factory[8 - i];
	}
	return ans;
}

int reservse_order(char str[]) {
	int ans = 0;
	for (int i = 0; i < 9; ++i) {
		for (j = 0; j < i; ++j) {
			if (str[i] == 9) break;
			if (str[j] == 9) continue;
			if (str[i] < str[j]) ans++;
		}
	}
	return ans % 2;
}

inline bool can(int x, int y) {
	if (x >= 0 && x <= 2 && y >= 0 && y <= 2) return true;
	return false;
}

bool bfs_expand(queue<int> &que, bool flag) {
	if (que.empty()) return false;
	int pos = que.front(); que.pop();
	state &s = states[pos];
	int space = s.space;
	int x = space / 3, y = space % 3;
	for (int i = 0; i < 4; ++i) {
		int pos_x = x + dir[i][0], pos_y = y + dir[i][1];
		if (can(pos_x, pos_y)) {
			states.push_back((state) { s.eight, 0, 0, pos, 0 });
			state &t = states[states.size() - 1];
			t.space = pos_x * 3 + pos_y;
			swap(t.eight[k], t.eight[t.space]);
			t.state = get_hash(t.eight);
			char _flag = flag ? 1 : 0;
			if (vis[t.state] != 2 - _flag && reservse_order(t.eight) == 0) {
				t.move = get_move(i);
				if (vis[t.state] == 1 + _flag) {
					found = true;
					found_pos = states.size() - 1;
					return true;
				}
				vis[t.state] = 2 - _flag;
				que.push(states.size());
			} else {
				states.pop_back();
			}
		}
	}
}

void bfs() {
	states.clear();
	memset(vis, 0, sizeof(vis));
	queue<int> q1, q2;
	states.push_back(q1);
	states.push_back(q2);
	q1.push(0);
	q2.push(1);
	vis[s1.state] = vis[s2.state] = 1;
	s1.father = s2.father = -1;
	while (!q1.empty() || !q2.empty()) {
		if (bfs_expand(q1, true)) return ;
		if (bfs_expand(q2, false)) return ;
	}
}

void output_path(int pos) {
	if (pos == -1) return;
	output_path(states[pos].father);
	cout << states[pos].move;
}

void output_path_resevse() {
	
}

int main() {
	for(int i = 0; i < 9; i++)
		s2.eight[i] = i + 1;
	s2.space = 8;
	s2.state = Gethash(s2.eight);

	char c;
	while (cin >> c) {
		if (c == 'x') s1.eight[0] = 9, s1.space = 0;
		else s1.eight[0] = c - '0';
		for (int i = 1; i < 9; ++i) {
			cin >> c;
			if (c == 'x') s1.eight[i] = 9, s1.space = 0;
			else s1.eight[i] = c - '0';
		}

		s1.state = get_hash(s1.eight);
		if (reservse_order(s1.eight) == 1) {
			cout << "unsolvable" << endl;
			continue;
		}
		found = false;
		bfs();
		if (!found) {
			cout << "unsolvable" << endl;
		} else {
			output_path(found_pos);
			output_path_resevse();
			cout << endl;
		}
	}
	return 0;
}
