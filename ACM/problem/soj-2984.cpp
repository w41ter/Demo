#include <iostream>
#include <vector>

using namespace std;

typedef vector<long long> vec;
typedef vector<vec> mat;

mat mul(mat &a, mat &b) {
	mat c(a.size(), vec(b[0].size()));
	for (int i = 0; i < a.size(); ++i) {
		for (int k = 0; k < b.size(); ++k) {
			for (int j = 0; j < b[0].size(); ++j) {
				c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % 10000;
			}
		}
	}
	return c;
}

mat pow(mat &a, long long n) {
	mat b(a.size(), vec(a.size()));
	for (int i = 0; i < a.size(); ++i) {
		b[i][i] = 1;
	}
	while (n > 0) {
		if (n & 1) b = mul(b, a);
		a = mul(a, a);
		n >>= 1;
	}
	return b;
}

int main() {
	long long int n;
	while (cin >> n && n != -1) {
		if (n == 0) {
			cout << 0 << endl;
			continue;
		}
		mat a(2, vec(2));
		a[0][0] = a[0][1] = a[1][0] = 1;
		mat b = pow(a, n);
		cout << b[0][1] << endl;
	}
	return 0;
}