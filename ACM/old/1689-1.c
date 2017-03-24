#include <stdio.h>
#include <string.h>

#define NUMBER_SIZE 36000

void mul(unsigned char a[], unsigned long k, int m)
{
    int i;
    unsigned long p;
    unsigned long c = 0;
	
    for ( i = NUMBER_SIZE - 1; i >= m; i--)
    {
		p = a[i] * k + c;
		a[i] = (unsigned char)(p % 10);
		c = p / 10;
    }
	
    while (c > 0)
    {
		a[i] = (unsigned char)(c % 10);
		i--;
		c /= 10;
    }
}

int main()
{
	int length = 0, number = 0;
	scanf("%d", &length);
	
	unsigned char data[NUMBER_SIZE];
	
	int i = 0, j = 0;
	for (; i < length; i++)
	{
		
		scanf("%d", &number);
		memset(data, 0, sizeof(data));
		data[NUMBER_SIZE-1] = 1;
		while (number > 1)
		{
			j = 0;
			/* 读取长度 */
			while (data[j] == 0)
				j++;
				
			mul(data, number--, j);
		}
		
		/* 显示结果 */
		j = 0;
		while (data[j] == 0)
				j++;
		
		while (j < NUMBER_SIZE)
			putchar(data[j++] + 48);
			
		putchar('\n');
	}
	
	system("PAUSE");
	return 0;
}
