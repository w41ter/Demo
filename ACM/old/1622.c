#include <stdio.h>

int main()
{
	int a = 0, b = 0;
	
	while (scanf("%d", &a) == 1)
		b += a;
	
	printf("%d", b);
}
