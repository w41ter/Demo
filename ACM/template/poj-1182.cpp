#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;

const int MAX_N = 100000 * 4;
int N, K;
int T[MAX_N], X[MAX_N], Y[MAX_N];

int parent[MAX_N];

int union_set_init(int n) {
	for (int i = 0; i < n; ++i) parent[i] = i;
}

int union_set_find(int x) {
	if (parent[x] == x) 
		return x;
	else 
		return parent[x] = union_set_find(parent[x]);
}

void union_two_set(int x, int y) {
	x = union_set_find(x);
	y = union_set_find(y);
	if (x != y)
		parent[x] = y;
}

bool union_set_same(int x, int y) {
	return union_set_find(x) == union_set_find(y);
}

void solve() {
	union_set_init(N * 3);

	int ans = 0;
	for (int i = 0; i < K; ++i) {
		int t = T[i];
		int x = X[i] - 1, y = Y[i] - 1;

		if (x < 0 || N <= x || y < 0 || N <= y) {
			ans++;
			continue;
		}

		if (t == 1) {
			if (union_set_same(x, y + N) || union_set_same(x, y + 2 * N)) ans++;
			else {
				union_two_set(x, y);
				union_two_set(x + N, y + N);
				union_two_set(x + N * 2, y + N * 2);
			}
		} else {
			if (union_set_same(x, y) || union_set_same(x, y + 2 * N)) ans++;
			else {
				union_two_set(x, y + N);
				union_two_set(x + N, y + N * 2);
				union_two_set(x + N * 2, y);
			}
		}
	}
	printf("%d\n", ans);;
}

int main() {
	//cin >> N >> K;
	scanf("%d%d", &N, &K);
	for (int i = 0; i < K; ++i) {
		//cin >> T[i] >> X[i] >> Y[i];
		scanf("%d%d%d", &T[i], &X[i], &Y[i]);
	}

	solve();
	return 0;
}