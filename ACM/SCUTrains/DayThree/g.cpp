#include <iostream>

using namespace std;

const int N = 4001;
int rounds[N];
int max_num, min_num, x, k;

int main()
{
	cin >> x >> k;
	while (--k >= 0)
	{
		int a, b, c;
		cin >> a >> b;
		rounds[b] = 1;
		
		if (a == 1)
			rounds[b + 1] = 1, cin >> c;
	}
	rounds[0] = 1;
	
	for (int i = 1; i < x; ++i)
	{
		int num = 0, j;
		for (j = i; j < x; ++j)
			if (rounds[j] == 0)
			{
				i = j;
				break;
			}
			
		if (j == x)
			break;
		
		for (j = i; j < x; ++j)
			if (rounds[j] == 1)
			{
				num = j - i;
				i = j;
				break;
			}
		if (j == x)
			num = j - i, i = j; //, cout << num << endl;;
		
		min_num += num / 2;
		if (num % 2 == 1)
			min_num++;
		max_num += num;
	}
	cout << min_num << ' ' << max_num << endl;
	return 0;
}