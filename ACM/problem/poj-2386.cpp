#include <iostream>
#include <string>
#include <queue>


using namespace std;

typedef pair<int, int> pii;

const int MAX_N = 100 + 5;
int N, M;
char field[MAX_N][MAX_N];
int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1}, dy[] = {0, 1, 1, 1, 0, -1, -1, -1 };

int can(int i, int j) {
	if (field[i][j] == 'W') return 1;
	else return 0;
}

int bfs(int i, int j) {
	queue<pii> que;
	que.push(pii(i, j));
	field[i][j] = '.';
	while (!que.empty()) {
		pii p = que.front(); que.pop();
		for (int d = 0; d < 8; ++d) {
			int i1 = p.first + dx[d], j1 = p.second + dy[d];
			if (can(i1, j1)) {
				field[i1][j1] = '.';
				que.push(pii(i1, j1));
			}
		}
	}
	return 1;
}

int solve() {
	int ans = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (field[i][j] == 'W') {
				ans += bfs(i, j);
			}
		}
	}
	return ans;
}

int main() {
	cin >> N >> M;

	for (int i = 0; i < N; ++i) {
		cin >> field[i];
	}

	cout << solve() << endl;
	return 0;
}