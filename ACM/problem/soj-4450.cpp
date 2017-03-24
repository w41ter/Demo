#include <iostream> 
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

const double EPS = 1e-10;

double add(double a, double b) {
	if (fabs(a + b) < EPS * (fabs(a) + fabs(b))) return 0;
	return a + b;
}

struct P {
	double x, y;
	P() {};
	P(double x, double y) : x(x), y(y) {}
	P operator + (P p) {return P(add(x, p.x), add(y, p.y));}
	P operator - (P p) { return P(add(x, -p.x), add(y, -p.y));}
	P operator * (double d) { return P (x * d, y * d);}
	double dot(P p) { return add(x * p.x, y * p.y);}
	double det(P p) { return add(x * p.y, -y * p.x); }

};

bool cmp_x(const P& p, const P& q) {
	if (p.x != q.x) return p.x < q.x;
	return p.y < q.y;
}

void convex_hull(vector<P> &qs, P *ps, int n) {
	sort(ps, ps + n, cmp_x);
	int k = 0;
	qs.resize(n * 2);
	for (int i = 0; i < n; ++i) {
		while (k > 1 && (qs[k-1] - qs[k-2]).det(ps[i] - qs[k-1]) <= 0) k--;
		qs[k++] = ps[i];
	}
	for (int i = n-2, t = k; i >= 0; --i) {
		while (k > t && (qs[k-1] - qs[k-2]).det(ps[i] - qs[k-1]) <= 0) k--;
		qs[k++] = ps[i];
	}
	qs.resize(k-1);
}

double dist(P p, P q) {
	return (p - q).dot(p - q);
}

const int MAX_N = 1000 + 10;
int N;
P ps[MAX_N];
void solve() {
	vector<P> qs;
	convex_hull(qs, ps, N);

	int sum_x = 0, sum_y = 0;
	for (int i = 0; i < qs.size(); ++i) {
		P p = qs[i];
		sum_x += p.x;
		sum_y += p.y;
	}
	cout << sum_x << ' ' << sum_y << endl;
}

int main() {
	while (cin >> N && N) {
		for (int i = 0; i < N; ++i) {
			cin >> ps[i].x >> ps[i].y;
		}
		solve();
	}
	return 0;
}