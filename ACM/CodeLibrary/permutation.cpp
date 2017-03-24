#include <stdio.h>

void Swap(int *left, int *right) 
{
	int tmp = *left;
	*left = *right;
	*right = tmp;
}

// 
// n - length of a 
// cur - cur position to a
// 
void Permutation(int n, int *a, int cur)
{
	if (n == cur)
	{
		for (int i = 0; i < n; i++) 
			printf("%d ", a[i]);
		putchar('\n');
	}
	else 
	{
		for (int i = cur; i < n; i++)
		{
			Swap(&a[cur], &a[i]);
			Permutation(n, a, cur + 1);
			Swap(&a[cur], &a[i]);
		}
	}
}

int main()
{
	int a[] = {1, 2, 3};
	Permutation(3, a, 0);
	return 0;
}