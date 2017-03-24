#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5 + 10;
long long int sum, _max;
int n, A, B, L;

int main() 
{
	int t = 0;
	scanf("%d", &t);
	int _case = 0;
	while (++_case <= t)
	{
		scanf("%d %d %d %d", &n, &A, &B, &L);
		int l, r, r1 = 0;
		sum = 0, _max = 0;
		for (int i = 0; i < n; ++i)
		{
			int l, r;
			scanf("%d %d", &l, &r);
			sum -= B * (l - r1);
			sum += A * (r - l);
			r1 = r;
			_max = max(sum, _max);
		}

		printf("Case #%d: %I64d\n", _case, _max);
	}
	return 0;
}