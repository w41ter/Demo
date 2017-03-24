#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 1000 + 10;
char trangle[MAX_N][2 * MAX_N];
int N, dp[MAX_N][2 * MAX_N];

int solve() {
	int ans = 0;
	memset(dp[0], 0, N * 2 * sizeof(char));
	for (int i = 1; i <= N; ++i) {
		for (int j = 0; j < 2 * (N - i) - 1 - ; ++j) {
			if (trangle[i][j] == 'X') {
				dp[i][j] = -1;
			} else if (trangle[i - 1][j] != 'X' && trangle[i - 1][j + 1] != 'X' && trangle[i - 1][j + 2] != 'X') {
				
			}
		}
	}
}

int main() {
	while (cin >> N && N) {
		for (int i = 1; i <= N; ++i) {
			cin >> trangle[i];
		}
		cout << solve() << endl;
	}
	return 0;
}