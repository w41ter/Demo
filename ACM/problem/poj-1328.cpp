#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

struct point { double left, right;};

point p[2010];

bool operator < (point a, point b) { return a.left < b.left;}

int main() {
	int n;
	double r;
	int _case = 0;
	while (cin >> n >> r && (n || r)) {
		bool flag = false;
		for (int i = 0; i < n; ++i) {
			double a, b;
			cin >> a >> b;
			if (fabs(b) > r) {
				flag = true;
			} else {
				p[i].left = a * 1.0 - sqrt(r * r - b * b);
				p[i].right = a * 1.0 + sqrt(r * r - b * b);
			}
		}
		cout << "Case " << ++_case << ": ";
		if (!flag) {
			int count = 1;
			sort(p, p + n);
			point t = p[0];
			for (int i = 0; i < n; ++i) {
				if (p[i].left > t.right) {
					count++;
					t = p[i];
				} else if (p[i].right < t.right) {
					t = p[i];
				}
			} 
			cout << count << endl;
		} else {
			cout << -1 << endl;
		}
	}

}