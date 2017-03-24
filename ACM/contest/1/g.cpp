#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct pot {
	int left, right, parent;
};

int map[101][101], level[101][101];
vector<pot> pot_total;
int A, B, C;

pot opreate(pot p, int op) {
	switch (op) {
		case 1:
			p.left = A;
			break;
		case 2:
			p.right = B;
			break;
		case 3:
			p.left = 0;
			break;
		case 4:
			p.right = 0;
			break;
		case 5:
			if (p.left > B - p.right) {
				p.left -= B - p.right;
				p.right = B;
			} else {
				p.right += p.left;
				p.left = 0;
			}
			break;
		case 6:
			if (p.right > A - p.left) {
				p.right -= A - p.left;
				p.left = A;
			} else {
				p.left += p.right;
				p.right = 0;
			}
			break;
	}
	return p;
}

int bfs() {
	queue<int> que;
	pot head = {0, 0, 0};
	que.push(0);
	pot_total.push_back(head);
	while (!que.empty()) {
		int pos = que.front(); que.pop();
		pot &p = pot_total[pos];
		if (p.left == C || p.right == C) return pos;
		for (int i = 1; i <= 6; ++i) {
			pot tmp = opreate(p, i);
			if (!map[tmp.left][tmp.right]) {
				level[tmp.left][tmp.right] = level[p.left][p.right] + 1;
				map[tmp.left][tmp.right] = i;
				tmp.parent = pos;
				pot_total.push_back(tmp);
				que.push(pot_total.size()-1);
			}
		}
	}
	return -1;
}

void output(int pos) {
	if (pos == 0) return ;
	pot &p = pot_total[pos];
	output(p.parent);
	switch (map[p.left][p.right]) {
		case 1:
			cout << "FILL(1)" << endl;
			break;
		case 2:
			cout << "FILL(2)" << endl;
			break;
		case 3:
			cout << "DROP(1)" << endl;
			break;
		case 4:
			cout << "DROP(2)" << endl;
			break;
		case 5:
			cout << "POUR(1,2)" << endl;
			break;
		case 6:
			cout << "POUR(2,1)" << endl;
			break;
	}
}

int main() {
	pot_total.resize(100000);
	cin >> A >> B >> C;
	int pos = bfs();
	if (pos == -1) cout << "impossible" << endl;
	else {
		cout << level[pot_total[pos].left][pot_total[pos].right] << endl;
		output(pos);
	}
	return 0;
}