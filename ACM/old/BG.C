#include <stdio.h>

int main() 
{
	int i = 0;
	scanf("%d", &i);
	while (i != 0)
	{
		i = (i+1)/2;
		printf("%d\n", i);
		scanf("%d", &i);
	}
	return 0;
}
