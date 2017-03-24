#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUMBER 30 + 1
int main()
{
	char string[NUMBER];
	int i = 0, index = 0, length = 0;
	
Begin:
	scanf("%s", string);
	if (string[0] != '#')
	{
		scanf("%d", &index);
		length = strlen(string);
		i = length - index;
		
		while (i < length)
			putchar(string[i++]);
		i = 0;	
		length -= index;
		while (length > i)
			putchar(string[i++]);
			
		putchar('\n');
		goto Begin;
	}
	system("PAUSE");
	
	return 0;
}

