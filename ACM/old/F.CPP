#include <stdio.h>
#define ALL_ZEROS(a, b, c, d, e, f) ((a == 0)&&(b == 0)&&(c == 0)&&(d == 0)&&(e == 0)&&(f == 0))

int main() 
{
	int x1, y1, x2, y2, x3, y3;
	int sum;
	
Begin:
	scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3);
	if (ALL_ZEROS(x1, y1, x2, y2, x3, y3))
		return 0;
		
	sum = (x1 + y1) * 2;
	printf("%d-%d\n", (sum - (x1 + x2 + x3)), (sum - y1 -y2 -y3));
	goto Begin;
	
	return 0;
}
