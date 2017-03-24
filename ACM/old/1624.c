#include <stdio.h>
#include <string.h>

int main()
{
	char str[100];
	
	memset(str, 0, 100);
	while (gets(str) != NULL)
	{
		int i = 0;
		while (str[i] != 0)
		{
			if (str[i] == ' ')
			{
				i++;
				continue;
			}
			putchar(str[i]);
			i++;
		}
		putchar('\n');
		memset(str, 0, 100);
	}
	
	return 0;
}
