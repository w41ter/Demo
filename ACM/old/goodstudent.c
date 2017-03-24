#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	long a, b, c;
	char op, d;
	char buffer[10], data[10];
	int length = 0;
	
	while (scanf("%ld%c%ld=", &a, &op, &b) != EOF)
	{
		if (op == '-')
			a = a-b;
		else 
			a = a+b;
			
		scanf("%s", data);
		sprintf(buffer, "%d", a);
		
		if (strcmp(buffer, data) == 0)
		{	
			length++;
		}
	}
	printf("%d\n", length);
	return 0;
}

