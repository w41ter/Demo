#include <stdio.h>

int main() {
	float l,p,q;
    scanf("%f%f%f",&l,&p,&q);
    printf("%.8f\n",l/(p+q)*p);
	return 0;
}