#include <stdio.h>
#include <string.h>

#define MAX 10000 + 10
int main()
{
	int n = 0;
	int data[MAX];
	while (scanf("%d", &n) == 1)
	{
		memset(data, 0, sizeof(data));
		
		for (int i = 0; i < n; i++)
			scanf("%d", &data[i]);	// ¶ÁÊý¾Ý
		
		int half = (n+1)>>2;
		int cur = 0, next = 0;
		int index = 1, num;
		bool first = true;
	
		while (next < n-1)
		{
			num = data[next];
			cur = next + 1;
			first = true;
			while (cur < n)
			{
				if (num == data[cur])
				{
					index++;
				}
				else if (first)
				{
					first = false;
					next = cur;
				}
				else 
				{
					if ((half-index) > (n-cur-1))
						break;
				}
				
				if (index >= half)
				{
					printf("%d\n", num);
					goto End;
				}
				cur++;
			}
		}
End:
		cur++;
	}
	
	getchar();
	return 0;
}
