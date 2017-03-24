#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
	int i = 0, j = 0;
	while (scanf("%d %d", &i, &j) == 2)
	{
		printf("%d\n", abs(i - j));
	}
	return 0;
}
