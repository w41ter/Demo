#include <stdio.h>
#include <math.h>

int main()
{
	double x1, x2, x3, x4, x5;
Begin:
	scanf("%lf %lf %lf %lf %lf", &x1, &x2, &x3, &x4, &x5);
	if ((x1 == 0) && (x2 == 0) && (x3 == 0) && (x4 == 0) && (x5 == 0))
	{
		return 0;
	}
	
	x1 = x1 + x2 + x3 + x4 + x5;
	if (fabs(x1) < 0.001)
		printf("%.3lf", 0.0);
	if (fabs(x1) < 0.001)
		if (a < 0)	printf("%d\n", -a)
		else printf("%d", a);
	printf("%.3lf\n", x1);
	goto Begin;
	
	return 0;
}
