#include <iostream>
#include <map>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;
int main()
{
	int *data = new int [101];
	int n = 0;
	
	for (int i = 1; i <= 100; i++)
	{
		int index = 4, count = 0;
		char buff[12], b[12];
		
		sprintf(b, "%d", i);
		int len1 = strlen(b), len2 = 0;
		
		while (true)
		{
			count = exp2(index);
			
			sprintf(buff, "%d", count);
			len2 = (strlen(buff)+1)/2;
			if (len2 > len1 && strncmp(buff, b, len1) == 0)
			{
				data[i] = index;
				break;
			}
			
			++;
		}
	}
	
	while (cin>>n && n)
	{
		cout<<data[n]<<endl;
	}
	
	delete []data;
	return 0;
}
