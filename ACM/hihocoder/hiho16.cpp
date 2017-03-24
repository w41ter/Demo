#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;
int d[N][22], n, l, r;

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)  scanf("%d", &d[i][0]);
	for (int j = 1; (1<<j) <= n; ++j) 
		for (int i = 0; i + (1<<j) - 1 < n; ++i)
			d[i][j] = min(d[i][j-1], d[i + (1<<(j-1))][j-1]);

	scanf("%d", &n);
	while (n--) {
		scanf("%d %d", &l, &r);
		int k = log(r-l+1)/log(2);
		printf("%d\n", min(d[l-1][k], d[r-(1<<k)][k]));
	}
	return 0;
}
