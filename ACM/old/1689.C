#include <stdio.h>
#include <string.h>
#include <stdlib.h>

inline void muiply(char *szBuffer, char *str)
{
	register char strSum[36001];
	char *p = str;
	int indexA = 0, indexB = 0; 
	int sum = 35999;
	
	while (*p != '\0')
	{
		*p++ -= 48;
		indexA++;
	}
	
	p = szBuffer;
	while (*p != '\0')
	{
		*p++ -= 48;
		indexB++;
	}
	
	memset(strSum, 0, sizeof(strSum));

	indexA--;
	indexB--;
	
	int i = 0, j = 0, index = 0;
	for (i = indexA; i >= 0; i--)
	{
		index = sum;
		for (j = indexB; j >= 0; j--)
		{
			strSum[index--] += szBuffer[j] * str[i];
		}
		
		j = sum;
		while (j >= 0)
		{
			if (strSum[j] > 9)
			{
				strSum[j - 1] += strSum[j] / 10;
				strSum[j] = strSum[j] % 10;
			}
			j--;
		}
		sum--;
	}
		
	sum = 0;
	while (strSum[sum] == 0)
		sum++;
	
	indexA = sum;
	while (indexA < 36000)
	{
		strSum[indexA++] += 48;
	}
	
	memset(szBuffer, 0, sizeof(szBuffer));
	sprintf(szBuffer, "%s", &strSum[sum]);
}

int main()
{
	int i = 0, num = 0, number = 0;
	char str[6];
	register char strSum[36001];
	
	scanf("%d", &num);
	memset(str, 0, sizeof(str));
	for (; i < num; i++)
	{
		scanf("%d", &number);
		strSum[0] = '1';
		strSum[1] = '\0';
		
		while (number > 1)
		{
			memset(str, 0, sizeof(str));
			sprintf(str, "%d", number--);
			muiply(strSum, str);
		}
		
		printf("%s\n", strSum);
	}
	
	return 0;
}

