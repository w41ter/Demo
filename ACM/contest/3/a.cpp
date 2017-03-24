#include <iostream>
#include <algorithm>

using namespace std;

const int maxnode = 1000 * 1005;
const int max_n = 1005;
const int max_m = 1005;

void print();

struct DLX {
	int size, n, m, cur_line, sum, ans[max_n];
	int u[maxnode], d[maxnode], r[maxnode], l[maxnode], col[maxnode], row[maxnode];
	void init(int _n, int _m) {
		n = _n; m = _m;
		size = m; cur_line = 0;
		for (int i = 0; i <= _m; ++i) {
			u[i] = d[i] = i;
			r[i] = i + 1;
			l[i] = i - 1;
		}
		l[0] = _m; r[_m] = 0;
	}

	void setupdown() {
		d[size] = col[size]; 
		u[size] = u[col[size]];
		d[u[size]] = size;
		u[d[size]] = size;
	}

	void setleftright() {
		r[size] = r[size-1]; l[size] = size - 1;
		l[r[size]] = size; r[l[size]] = size;
	}

	void add_line(int n, int array[]) {
		cur_line++;
		int k = 0;
		for (int i = 0; i < n; ++i) {
			row[++size] = cur_line;
			col[size] = array[i];
			setupdown();
			if (!k) {
				l[size] = r[size] = size; k++;
			} else {
				setleftright();
			}
		}
	}

	void remove_col(int _c) {
		l[r[_c]] = l[_c];
		r[l[_c]] = r[_c];

		int i = d[_c];
		while (i != _c) {
			int j = r[i];
			while (j != i) {
				u[d[j]] = u[j];
				d[u[j]] = d[j];
				j = r[j];
			}
			i = d[i];
		}
	}

	void resume_col(int _c) {
		l[r[_c]] = _c;
		r[l[_c]] = _c;

		int i = u[_c];
		while (i != _c) {
			int j = r[i];
			while (j != i) {
				u[d[j]] = j;
				d[u[j]] = j;
				j = r[j];
			}
			i = u[i];
		}
	}

	bool dance(int _d) {
		int c1 = r[0];
		if (c1 == 0) { sum = _d; return true; }
		remove_col(c1);
		int i = d[c1];
		//cout << "i = " << i << " c1 = " << c1 << endl;
		while (i != c1) {
			ans[_d] = row[i];
			int j = r[i];
			while (j != i) {
				remove_col(col[j]);
				j = r[j];
			}
			if (dance(_d + 1)) return true;
			j = l[i];
			while (j != i) {
				resume_col(col[j]);
				j = l[j];
			}
			i = d[i];
		}
		resume_col(c1);
		return false;
	}
};

DLX dance;

void print() {
	int total = dance.m + 1;
	for (int i = 1; i <= dance.n; ++i) {
		for (int j = 1; j <= dance.m; ++j) {
			if (dance.col[total] == j && dance.row[total] == i) {
				cout << 1 << " ";
				total++;
			} else {
				cout << 0 << " ";
			}
		}
		cout << endl;
	}
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		dance.init(n, m);
		for (int r = 1; r <= n; ++r) {
			int total, c[max_m];
			cin >> total;
			for (int i = 0; i < total; ++i) {
				cin >> c[i];
			}
			dance.add_line(total, c);
		}
		if (!dance.dance(0)) {
			cout << "NO" << endl;
			continue;
		}
		cout << dance.sum;
		for (int i = 0; i < dance.sum; ++i) {
			cout << " " << dance.ans[i];
		}
		cout << endl;
	}
	return 0;
}