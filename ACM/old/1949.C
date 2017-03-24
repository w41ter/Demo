#include <stdio.h>

int main()
{
	int i = 0;
Begin:
	scanf("%d", &i);
	if (i != 0)
	{
		i = ((i % 2) == 0) ? (i / 2) : ((i + 1) / 2);
		printf("%d", i);
		goto Begin;
	}
	
	return 0;
}

