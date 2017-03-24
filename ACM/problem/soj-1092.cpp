#include <iostream>

using namespace std;

long long a, n, x, y;

long long execd(long long a, long long b, long long &x, long long &y) {
	long long ret = a;
	if (b != 0) {
		ret = execd(b, a % b, y, x);
		y -= (a/b)*x;
	} else {
		x = 1;
		y = 0;
	}
	return ret;
}

int main() {
	while (cin >> a >> n && (a || n)) {
		execd(a, n, x, y);
		if (x < 0) x += n;
		cout << x << endl;
	}
	return 0;
}