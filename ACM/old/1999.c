#include <stdio.h>
#include <string.h>

char s[] = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";
int main() 
{
	int i, c = 0;
	while ((c = getchar()) != EOF)
	{
		
		for (i = 0; s[i] && s[i] != c; i++);
		if (s[i]) putchar(s[i-1]);
		else if (c == '\n')
		{
			putchar('\n');
			putchar('\r');
		} 
		else putchar(c);
			
	}
	return 0;
}
