#include <stdio.h>

int s[500000], t[500000];
long long count = 0;

void merge_sort(int x, int y)
{
	if (y-x > 1)
	{
		int m = x + (y-x)/2, p = x, q = m, i = x;
		merge_sort(x, m);
		merge_sort(m, y);
		while (p < m || q < y)
		{
			if (q >= y || (p < m && s[p] <= s[q]))	t[i++] = s[p++];
			else t[i++] = s[q++], count += m-p;
		}
		for (i = x; i < y; i++) s[i] = t[i];
	}
}

int main() 
{
	int n = 0;
	while ((scanf("%d", &n) == 1) && n) 
	{
		int i = 0;
		while (i < n)
			scanf("%d", &s[i++]);
			
		count=0;
		merge_sort(0, n);
		
		printf("%lld\n", count);
	}
	return 0;
}
