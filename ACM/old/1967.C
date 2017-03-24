#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ALL_ZEROES(a, b, c, d) ((a == 0) && (b == 0) && (c == 0) && (d == 0))

int main()
{
	float a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0;
Begin:	
	scanf("%f%f%f%f%f", &a1, &a2, &a3, &a4, &a5);
	if (ALL_ZEROES(a1, a2, a3, a4))
	{
		system("PAUSE");
		return 0;
	}
	a1 = a1 + a2 + a3 + a4 + a5;
	if (fabs((double)a1) < 0.001)
		if (a1 < 0)
			printf("%.3f\n", -a1);
		else 
			printf("%.3f\n", a1);
	else 
		printf("%.3f\n", a1);
	goto Begin;
	
}
