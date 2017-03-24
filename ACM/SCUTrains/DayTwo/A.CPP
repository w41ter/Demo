
#include<cstdio>

using namespace std;
int f1(int a,int b,int c)
{
	if(a+b>c&&a+c>b&&b+c>a)
		return 1;
	else
		return 0;
}

int f2(int a,int b,int c)
{         
	if(a+b==c||a+c==b||b+c==a)
		return 1;
	else
		return 0;
}

int main()
{
	int a[4];
	scanf("%d%d%d%d",&a[1],&a[2],&a[3],&a[4]);
	
	if(f1(a[1],a[2],a[3])||f1(a[1],a[2],a[4])||f1(a[1],a[4],a[3])||f1(a[2],a[4],a[3]))
		printf("TRIANGLE\n");
	else if(f2(a[1],a[2],a[3])||f2(a[1],a[2],a[4])||f2(a[1],a[4],a[3])||f2(a[2],a[4],a[3]))
		printf("SEGMENT\n");  
	else 
		printf("IMPOSSIBLE\n"); 
	
    return 0;
}