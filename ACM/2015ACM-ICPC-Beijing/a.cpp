#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 105;

double x_p[N], y_p[N];
double map[N][N];

double distance(double x1, double y1, double x2, double y2)
{
	double x = (x1 - x2) * (x1 - x2), y = (y1 - y2) * (y1 - y2);
	return sqrt(x + y);
}

int get_value(double d) {
	int a = ceil(d), b = (int)d;
	if (a == b)return a + 1;
	else return a;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		memset(map, 0, sizeof(map));

		int m, n;
		scanf("%d %d", &m, &n);
		for (int i = 1; i <= m; ++i) {
			scanf("%lf %lf", &x_p[i], &y_p[i]);
		}

		for (int i = 1; i <= m; ++i) {
			for (int j = i + 1; j <= m; ++j) {
				map[i][j] = map[j][i] = distance(x_p[i], y_p[i], x_p[j], y_p[j]);
			}
		}

		int sum = 1010;
		for (int i = 1; i <= m; ++i) {
			double range[N];
			for (int j = 1; j <= m; ++j) {
				range[j] = map[i][j];
			}
			sort(range + 1, range + m + 1);
			for (int j = 1; j <= m; ++j) {
			}
			int _sum = get_value(range[n]);
			if(n == m || _sum < range[n + 1])
				sum = min(sum, _sum);
		}
		if (sum == 1010)
			printf("-1\n");
		else 
			printf("%d\n", sum);
	}
	return 0;
}

