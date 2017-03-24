#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <queue>
#include <string.h>

using namespace std;

int beg, en;
int dx[] = { 1000, 100, 10, 1 };
bool is_pri[10000];
int inqueue[10000];

int prime(int n) {
	int p = 0; 
	for (int i = 0; i <= n; ++i) is_pri[i] = true;
	is_pri[0] = is_pri[1] = false;
	for (int i = 2; i <= n; ++i) {
		if (is_pri[i]) {
			for (int j = 2 * i; j <= n; j += i) is_pri[j] = false;
		}
	}
	return p;
}

int bfs() {
	queue<int> que;
	que.push(beg);
	while (!que.empty()) {
		int p = que.front(); que.pop(); 
		if (p == en) return inqueue[p];
		for (int i = 0; i < 4; ++i) {
			int count = ((p / dx[i]) % 10) * dx[i];
			for (int j = 0; j < 10; ++j) {
				int c = j * dx[i];
				if (count == c || (i == 0 && j == 0)) continue;
				int v = p + c - count;
				if (p % 2 == 1 && is_pri[p] && !inqueue[v]) {
					inqueue[v] = inqueue[p] + 1;
					que.push(v);
				}
			}
		}
	}
	return -1;
}

int main() {
	prime(9999);
	int t;
	cin >> t;
	while (t--) {
		cin >> beg >> en;
		memset(inqueue, 0, sizeof(inqueue));
		int ans = bfs();
		if (ans == -1) cout << "Impossible" << endl;
		else cout << ans << endl;
	}
	return 0;
}

