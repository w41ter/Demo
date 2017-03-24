#include <stdio.h>
#include <string.h>

int main()
{
	char strA[505], strB[505];
	int strSum[1012];
	
	memset(strA, 0, sizeof(strA));
	memset(strB, 0, sizeof(strB));
	memset(strSum, 0, sizeof(strSum));
	while (scanf("%s%s", strA, strB) == 2)
	{
		int indexA = 0, indexB = 0; 
		int sum = 1011;
	
		while (strA[indexA] != '\0')
		{
			strA[indexA] -= 48;
			indexA++;
		}
		
		while (strB[indexB] != '\0')
		{
			strB[indexB] -= 48;
			indexB++;
		}
		
		indexA--;
		indexB--;
		
		int i = 0, j = 0, k = 0, index = 0;
		for (i = indexB; i >= 0; i--)
		{
			index = sum;
			for (j = indexA; j >= 0; j--)
			{
				strSum[index--] += strA[j] * strB[i];
			}
			
			k = sum;
			while (k >= 0)
			{
				if (strSum[k] > 9)
				{
					strSum[k - 1] += strSum[k] / 10;
					strSum[k] = strSum[k] % 10;
				}
				
				k--;
			}
			
			sum--;
		}
		
		for (i = 0; i < 1012; i++)
		{
			strSum[i] += 48;
		}
		
		k = 0;
		while ((k < 1011) && (strSum[k] == 48))
			k++;
		
		while (k < 1012)
			putchar(strSum[k++]);
			
		putchar('\n');
		
		memset(strA, 0, sizeof(strA));
		memset(strB, 0, sizeof(strB));
		memset(strSum, 0, sizeof(strSum));
	}
	
	return 0;
}
