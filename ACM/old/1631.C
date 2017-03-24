#include <stdio.h>
#include <stdlib.h>

#define NUMBER 100
int main()
{
	char szBuffer[NUMBER];
	int i = 0;
	scanf("%[^ ]", szBuffer);
	i = 0;
	while (szBuffer[i] != '\0')
		i++;
		
	while (i > 0)
		putchar(szBuffer[--i]);

	system("PAUSE");
	return 0;
}
