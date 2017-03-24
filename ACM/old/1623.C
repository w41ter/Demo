#include <stdio.h>
#include <string.h>

#define IsLowLette(c) (('a' <= c) && (c <= 'z'))

int toupper(int c)
{
	if (IsLowLette(c))
		return (c - 32);
		
	return c;
}

int main()
{
	char str[80];
	
	memset(str, 0, 80);
	while (scanf("%s", str) == 1)
	{
		int i = 0;
		while ((i < 80) && (str[i] != 0))
		{
			putchar(toupper(str[i]));
			i++;
		}
		putchar(' ');	
		memset(str, 0, 80);
	}
	
	getchar();
	return 0;
}
