#include <stdio.h>

int matrix[40][40];
long long int sum[40][40];
long long int temporary[40][40];
long long int n, k, m;
	
void SumOfMatrix(long long int k)
{
	if (k == 0) return ;
	
	SumOfMatrix(k - 1);
	
	for (int i = 0; i < n; i++)
	{	
		sum[i][i] += 1;
	}
	
	
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temporary[i][j] = 0;
			for (int l = 0; l < n; l++)
			{
				temporary[i][j] += matrix[i][l] * sum[l][j];
			}
		}
	}
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			sum[i][j] = temporary[i][j];
		}
	}
	
	return ;
}

int main() 
{
	while(~scanf("%d%d%d", &n, &k, &m))
	{
		for (int i = 0; i < n; i++) 
		{
			for (int j = 0; j < n; j++)
			{
				sum[i][j] = 0;
				scanf("%d", &matrix[i][j]);
			}
		}

		SumOfMatrix(k);

		for (int i = 0; i < n; i++) 
		{
			printf("%d", sum[i][0]);
			for (int j = 1; j < n; j++)
			{
				printf(" %d", sum[i][j] % m);
			}
			
			putchar('\n');
		}
	}
	return 0;
}

