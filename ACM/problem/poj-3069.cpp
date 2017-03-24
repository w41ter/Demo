#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_N = 2000 + 5;
int N, R, X[MAX_N];

int solve() {
	sort(X, X + N);
	int cur = 0, ans = 0;
	
	while (cur < N) {
		int pos = X[cur] + R;
		while (cur < N && X[cur] <= pos) cur++;
		pos = X[cur-1] + R;
		while (cur < N && X[cur] <= pos) cur++;
		ans++;
	}
	return ans;
}

int main() {
	while (true) {
		cin >> R >> N;
		if (R == -1 && N == -1) break;
		for (int i = 0; i < N; ++i) {
			cin >> X[i];
		}
		cout << solve() << endl;
	}

	return 0;
}