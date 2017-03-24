#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int add(int a, int b, int c)
{

}

int main()
{
	char strA[505], strB[505], strSum[506];
	
	memset(strA, 0, sizeof(strA));
	memset(strB, 0, sizeof(strB));
	memset(strSum, 0, sizeof(strSum));
	while (scanf("%s%s", strA, strB) == 2)
	{
		int indexA = 0, indexB = 0, c = 0, d = 0; 
		int sum = 505;
	
		while (strA[indexA] != '\0')
			indexA++;
		while (strB[indexB] != '\0')
			indexB++;
		
		while ((indexA > 0) && (indexB > 0))
		{
			c = strA[--indexA] + strB[--indexB] + d - 96;
			if ((c > 9) && (c < 20))
			{
				d = 1;
				strSum[sum--] = c + 38; 
			}
			else if (c >= 20)
			{
				d = 2;
				strSum[sum--] = c + 28; 
			} 
			else 
			{
				d = 0;
				strSum[sum--] = c + 48; 
			}
		}
		
		while (indexA > 0)
		{
			if (d != 0)
			{
				c = d + strA[--indexA] - 48;
				if (c > 9)
				{
					d = 1;
					strSum[sum--] = c + 38;
				}
				else 
				{
					d = 0;
					strSum[sum--] = c + 48;
				}
				continue;
			}
			
			strSum[sum--] = d + strA[--indexA];
		}
		
		while (indexB > 0)
		{
			if (d != 0)
			{
				c = d + strB[--indexB] - 48;
				if (c > 9)
				{
					d = 1;
					strSum[sum--] = c + 38;
				}
				else 
				{
					d = 0;
					strSum[sum--] = c + 48;
				}
				continue;
			}
			
			strSum[sum--] = d + strB[--indexB];
		}
		
		if (d != 0)
		{
			strSum[sum--] = d + 48;
			d = 0;
		}
		
		sum++;
		while ((sum < 505) && (strSum[sum] == 48))
			sum++;
		
		while (sum < 506)
		{
			putchar(strSum[sum++]);
		}
		
		putchar('\n');
		
		memset(strA, 0, sizeof(strA));
		memset(strB, 0, sizeof(strB));
		memset(strSum, 0, sizeof(strSum));
	}
	
	return 0;
}
