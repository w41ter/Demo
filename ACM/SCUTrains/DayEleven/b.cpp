#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

struct Employer
{
	int sup;
	int ab;
	int loyal;
	int next;
};

const int N = 5e4 + 5;
int n, m, _max[N];
struct Employer em[N];

int main()
{
	int T = 0;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d %d", &n, &m);
		memset(_max, -1, sizeof(int) * n + 5);
		for (int i = 1; i < n; ++i)
		{
			scanf("%d %d %d", &em[i].sup, &em[i].loyal, &em[i].ab);
			int m = _max[em[i].sup];
			if (m == -1) _max[em[i].sup] = i;
			else if (em[m].ab < em[i].ab || (em[m].ab == em[i].ab && em[m].loyal < em[i].loyal))
			{
				_max[em[i].sup] = i;
			}
		}
		while (m--)
		{
			int q = 0;
			scanf("%d", &q);
			printf("%d\n", _max[q]);
		}
	}
	return 0;
}