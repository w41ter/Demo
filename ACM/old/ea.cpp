#include<stdio.h>
#include<math.h>
#define e  2.718281828459                         

int main()
{
	double x,y,Y,X,begin,end,half;
	while(scanf("%lf",&Y)!=EOF)
	{
		if(Y==1) {printf("2.71828\n");continue;}
		begin=1;end=e;half=(begin+end)/2;
		y=log(e*Y)/(e*Y);
		while(fabs(begin-end)>=1e-7)                      //二分查找
		{
			x=log(half)/half;
			if(x<y) begin=half;
			else end=half;
			half=(begin+end)/2;
		}
		printf("%.5lf %.5lf\n",half,e*Y);                            //e*Y本身就是1根
	}
	return 0;

}
