#include <stdio.h>

int main()
{
	int n = 0, i, j;
	char buffer[50][50];
	scanf("%d", &n);
	while (n != 0)
	{
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
			{
				scanf("%d", &buffer[i][j]);
			}
		
		j = 0; i = 0;
		for (int k = 0; k < 2*n; k++)
		{
			for (i = 0; i <= k; i++)
			{
				if ((i >= n) || (k-i >= n))
					continue;
				printf("%d ", buffer[k-i][i]);
			}
			k++;
			for (i = 0; i <= k; i++)
			{
				if ((i >= n) || (k-i >= n))
					continue;
				printf("%d ", buffer[i][k-i]);
			}
		}
		putchar('\n');
		scanf("%d", &n);
	}	
	return 0;	
}

