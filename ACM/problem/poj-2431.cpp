#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct po {
	int pos;
	int val;
};

const int MAX_N = 1e4 + 10;

int L, P, N;
po stop[MAX_N];

bool compare(po a,po b) { return a.pos>b.pos; }

int main() {
	cin >> N;
	for (int i = N-1; i >= 0; --i) {
		cin >> stop[i].pos >> stop[i].val;
	}
	cin >> L >> P;
	sort(stop, stop + N, compare);
	stop[N].pos = 0; 
	stop[N].val = 0;

	priority_queue<int> que;
	int ans = 0, cur = L;
	for (int i = 0; i <= N; ++i) {
		int d = cur - stop[i].pos;
		while (P - d < 0) {
			if (que.empty()) {
				cout << -1 << endl;
				return 0;
			}
			P += que.top(); que.pop();
			ans++;
		}
		P -= d;
		cur = stop[i].pos;
		que.push(stop[i].val);
	}
	cout << ans << endl;
	return 0;
}