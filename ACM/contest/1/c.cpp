#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> pii;
int n, k, ans;
int map[100000];

bool equal(pii n) {return k == n.first;}

int insert(queue<pii> &que, pii p1) {
	if (p1.first >= 0 && p1.first <= 100000) {
		if (equal(p1)) 
			return ans = p1.second;
		else if (!map[p1.first]) {
			que.push(p1);
			map[p1.first] = 1;
		}
	}
	return -1;
}

void bfs() {
	queue<pii> que;
	insert(que, pii(n, 0));
	while (!que.empty()) {
		pii p = que.front(); que.pop();
		pii p1;	p1.second = p.second + 1;
		p1.first = p.first + 1;
		if (insert(que, p1) != -1) return;
		p1.first = p.first - 1;
		if (insert(que, p1) != -1) return;
		p1.first = p.first * 2;
		if (insert(que, p1) != -1) return;
	}
}

int main() {
	cin >> n >> k;
	if (n >= k) cout << n - k << endl;
	else {
		bfs();
		cout << ans << endl;
	}
	return 0;
}