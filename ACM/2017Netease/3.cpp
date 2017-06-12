#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        vector<int> worksets;
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            int t;
            cin >> t;
            worksets.push_back(t);
            sum += t;
        }

        int package = (sum + 1) / 2;
        vector<vector<int> > dp(n+1, vector<int>(package, sum));
        for (int i = 0; i < package; ++i) {
            dp[0][i] = 0;
        }
        for (int i = 1; i < n+1; ++i) {
            for (int j = 0; j < package; ++j) {
                dp[i][j] = dp[i-1][j];
                if (j > worksets[i]) {
                    dp[i][j] = max(dp[i-1][j-worksets[i]] + worksets[i], dp[i][j]);
                }
            }
        }
        int res = 0;
        for (int i = 0; i < package; ++i) {
            res = max(res, dp[n][i]);
        }
        cout << max(res, sum - res) << endl;
    }
    return 0;
}
