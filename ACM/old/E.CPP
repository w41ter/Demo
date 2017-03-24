#include <stdio.h>

long f91(long n)
{
	if (n <= 100)
		return f91(f91(n + 11));
	else 
		return n-10;
}

int main()
{
	long n = 0;
	while (scanf("%ld", &n))
	{
		if (n == 0)
			break;
			
		printf("f91(%ld) = %ld\n", n, f91(n));
	}
	
	return 0;
}
