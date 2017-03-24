#include <iostream> 
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAX_N = 2E4 + 10;
int N, L[MAX_N];

int main() {
	ll ans = 0;
	cin >> N;
	priority_queue<int, vector<int>, greater<int> > que;
	for (int i = 0; i < N; ++i) {
		int l;
		cin >> l;
		que.push(l);
	}

	while (que.size() > 1) {
		int l1 = que.top();que.pop();
		int l2 = que.top(); que.pop();

		ans += l1 + l2;
		que.push(l1 + l2);
	}

	cout << ans << endl;
	return 0;
}