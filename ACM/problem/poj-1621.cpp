#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 40000;
const int INF = 0x3ffffff;
int P, a[MAX_N], dp[MAX_N];

void solve() {
	fill(dp, dp + P, INF);
	for (int i = 0; i < P; i++) {
		*lower_bound(dp, dp + P, a[i]) = a[i];
	}
	printf("%d\n", lower_bound(dp, dp + P, INF) - dp);
}

int main() {
	int n;
	cin >> n;
	while (n--) {
		cin >> P;
		for (int i = 0; i < P; ++i) cin >> a[i];
		solve();
	}
	return 0;
}