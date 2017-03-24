#include <stdio.h>
#include <stdlib.h>

int main()
{
	int number = 0, need = 0;
	int i = 0, j = 0, k = 0;
	int total = 0;
	int *data;
Begin:	
	scanf("%d%d", &number, &need);
	if ((number == 0) && (need == 0))
		return 0;
		
	i = number;
	total = 0;
	data = (int*)malloc(sizeof(int) * i);
	while (i > 0)
		scanf("%d", &data[--i]);
	
	for (i = 0; i <= number-3; i++)
	{
		for (j = i+1; j <= number-2; j++)
		{
			if ((data[i] + data[j]) >= need)
			{
				continue;
			}
				
			for (k = j+1; k <= number-1; k++)
			{
				if ((data[i] + data[j] + data[k]) == need)
				{
					total++;
				}
			}
		}
	}
	free(data);
	
	printf("%d\n", total);
	
	goto Begin;
	
	return 0;
}
