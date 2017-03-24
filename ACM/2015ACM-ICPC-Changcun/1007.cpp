#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1000 + 10;
int a[N];
// int d[N][11];

// void RMQ_init(int n) {
// 	for (int i = 0; i < n; ++i) d[i][0] = a[i];
// 	for (int j = 1; (1<<j) <= n; ++j) 
// 		for (int i = 0; i + (1 << j) - 1 < n; ++i)
// 			d[i][j] = max(d[i][j-1], d[i + (i<<(j-1))][j-1]);
// }

// int RMQ(int l, int r) {
// 	int k = 0;
// 	while ((1<<(k+1)) <= r-l+1) k++;
// 	return max(d[l][k], d[r-(1<<k)+1][k]);
// }

int main() {
	std::ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) {
		memset(a, 0, sizeof(a));

		int n, q, l, r, _max;
		cin >> n;
		for (int i = 0; i < n; ++i) 
			cin >> a[i];

		//RMQ_init(n);

		cin >> q;
		for (int i = 0; i < q; ++i) {
			cin >> l >> r;
			for (_max = 0, --l; l < r; ++l)
				if (a[l] > _max) _max = a[l];
			cout << _max << endl;
		}
	}
	return 0;
}