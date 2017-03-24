#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <map>

using namespace std;

const int N = 150000+5;

struct Friends {
	int name;
	int value;
} ;

Friends f[N], tmp[N];
map<int, int> t;
char name[N][205];
priority_queue<Friends> Q;

bool operator < (const Friends &ls, const Friends &rls) {
		if (rls.value == ls.value) return ls.name > rls.name;
		return (rls.value > ls.value);
}

int cmp(const void *a, const void *b) {
	Friends * fa = (Friends*)a, *fb = (Friends*)b;
	if (fb->value == fa->value)
		return fa->name - fb->name;
	return fb->value - fa->value;
}

int main() {
	//std::ios::sync_with_stdio(false);

	int T;
	cin >> T;
	while (T--) {
		int k, m, q;
		cin >> k >> m >> q;

		for (int i = 0; i < k; ++i) {
			scanf("%s %d", name[i], &f[i].value);
			f[i].name = i;
		}

		t.clear();
		int pos = 0, num = 0;
		for (int i = 0; i < m; ++i) {
			scanf("%d %d", &pos, &num);
			t[pos] += num;
		}
		t[k] = k - pos;

		int cur = 0, last_pos = 0;
		for (auto b = t.begin(); b != t.end(); ++b) {
			int i = b->first;
			for (int j = last_pos; j < i; ++j)
				Q.push(f[j]);
			for (int j = 0; j < t[i] && !Q.empty(); ++j)
				tmp[cur + j] = Q.top(), Q.pop();
			if (cur + t[i] > i) cur = i;
			else cur += t[i];
			last_pos = i;	
		}

		for (int i = 0; i < q; ++i) {
			int que;
			cin >> que;
			cout << name[tmp[que-1].name] << " ";
		}
	}
	return 0;
}