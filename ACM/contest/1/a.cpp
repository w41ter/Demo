#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

int sum, n, k, dx, dy;
char map[10][10];

int dfs(int i, int j, int d) {
	if ((dx & 1 << i) || (dy & 1 << j)) return 0;
	if (d == 1) return 1;
	if (i+1 >= n) return 0;
	int ans = 0;
	dx |= 1 << i;
	dy |= 1 << j;
	for (int l = i + 1; l < n; ++l) {
		for (int k = 0; k < n; ++k) {
			if (map[l][k] != '.')
				ans += dfs(l, k, d-1);
		}
	}
	dx ^= 1 << i;
	dy ^= 1 << j;
	return ans;
}

int main() {
	while (cin >> n >> k && k != -1 && n != -1) {
		sum = 0;
		for (int i = 0; i < n; ++i) {
			cin >> map[i];
		}
		for (int i  = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (map[i][j] != '.') {
					dx = dy = 0;
					sum += dfs(i, j, k);
				}
					
			}
		}
		cout << sum << endl;
	}
}