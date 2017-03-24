#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

struct range { unsigned int left, right, index; };

unsigned int N;
range sche[50000 + 10];
unsigned int index[50000 + 10];

bool less_than(range l, range r) {
	if (l.left == r.left) return l.right < r.right;
	else return l.left < r.left;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> sche[i].left >> sche[i].right;
		sche[i].index = i;
	}

	sort(sche, sche + N, less_than);
	// for (int i = 0; i < N; ++i) {
	// 	cout << sche[i].left << ' ' << sche[i].right << endl;
	// }
	unsigned int ans = 0;
	priority_queue<pii, vector<pii>, greater<pii> > que;
	que.push(pii(0, ++ans));
	// que.push(pii(1, ++ans));
	// que.push(pii(2, ++ans));
	// que.push(pii(3, ++ans));
	// que.push(pii(4, ++ans));
	// que.push(pii(5, ++ans));

	// while (!que.empty()) {
	// 	pii p = que.top(); que.pop();
	// 	cout << p.first << ' ' << p.second << endl;
	// }
	// return 0;

	for (int i = 0; i < N; ++i) {
		pii left = que.top(); que.pop();
		//cout << sche[i].index << " ";
		if (sche[i].left >= left.first) {
			//cout << "cur :" << left.first << ' ' << left.second << endl;
			que.push(pii(sche[i].right + 1, left.second));
			index[sche[i].index] = left.second;
		} else {
			//cout << "next :" << sche[i].right + 1 << ' ' << ans+1 << endl;
			que.push(left);
			que.push(pii(sche[i].right + 1, ++ans));
			index[sche[i].index] = ans;
		}
	}

	cout << ans << endl;
	for (int i = 0; i < N; ++i) 
		cout << index[i] << endl;

	return 0;
}