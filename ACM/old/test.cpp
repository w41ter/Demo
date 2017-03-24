#include<stdio.h>
#include<stdlib.h>

int chazhao(char s[],int ch);
int main(void)
{
	int a;
	char b[100];
	printf("please input a string:");
	scanf("%s",b);
	printf("please input a zifu:");
	scanf(" %c",&a);
	printf("the place of zifu is:%d\n",chazhao(b,a));
	system("PAUSE");
	return 0;
}

int chazhao(char s[],int ch)
{
	int i = 0, j=0;
	int a;
	while(s[i]!='\0')
	{
		i++;
		j++;
	}
	while(s[i]!='\0') 
	{
		if(ch==s[i])
		{
			break;
		}
		else if(i=j)
		{
			return -1;
			break;
		}
		else
		i++;
	}
	a=i+1;
	return a;
}
