#include <iostream> 
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct _point {
	int pos;
	int depth;
};

const int N = 10e5 + 5;

map<string, int> name_map;
map<int, string> index_map;
vector<int> tree[N];
int last[N], length;
_point _array[2*N][20];

bool operator < (const _point &a, const _point &b) {
	return a.depth < b.depth;
}

int get_id(string &str) {
	if (name_map.count(str) == 0) {
		int i = name_map[str] = name_map.size() - 1;
		//cout << str << " position is :" << i << endl;
		index_map[i] = str;
	}
	return name_map[str];
}

void dfs(int n, int d) {
	_array[length++][0] = { n, d };
	//cout << n << " ";
	for (int i = 0; i < tree[n].size(); ++i) dfs(tree[n][i], d + 1);
	//cout << n << " ";
	_array[length][0] = { n, d };
	last[n] = length++;
}

void RMQ_init(int n) {
	for (int j = 1; (1<<j) <= n; ++j) 
		for (int i = 0; i + (1<<j) - 1 < n; ++i) {
			_array[i][j] = min(_array[i][j-1], _array[i+(1<<(j-1))][j-1]);
			//cout << "i :" << i << " j:" << j << " _array:" << _array[i][j].depth << endl;
		}
}

const _point RMQ(int l, int r) {
	int k = 0;
	while ((1<<(k+1)) <= r-l+1) k++;
	//cout << "(" << l << ',' << k << ")" << "(" << r << ',' << k << ")" << endl;
	//cout << _array[l][k].depth << ',' <<  _array[r-(1<<k)+1][k].depth << endl;
	return min(_array[l][k], _array[r-(1<<k)+1][k]);
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		string name1, name2;
		cin >> name1 >> name2;
		int id1 = get_id(name1), id2 = get_id(name2);
		tree[id1].push_back(id2);
	}

	dfs(0, 1);
	RMQ_init(2*n);

	//cout << _array[5][0].depth << " sadfasd "<< _array[6][0].depth<< " " << _array[5][1].depth <<endl;
	cin >> n;
	while (n--) {
		string name1, name2;
		cin >> name1 >> name2;
		int id1 = get_id(name1), id2 = get_id(name2);
		int l = last[id1], r = last[id2];
		if (r < l) { int t = l; l = r; r = t; }
		//cout << "l is :" << l << " r is :" << r << endl;
		cout << index_map[RMQ(l, r).pos] << endl;
	}
	return 0;
}