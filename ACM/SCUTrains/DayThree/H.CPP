#include <iostream>

using namespace std;

int m, n;

int main()
{
	cin >> n >> m;
	if (n - 1 > m || m - 2 > 2 * n)
	{
		cout << -1 << endl;
		return 0;
	}
	if (n - 1 == m)
	{
		for (int i = 0; i < n + m; ++i)
			cout << (i % 2 == 0 ? 0 : 1); 
		return 0;
	}
	else
	{
		int num_of_two = m - n;
		for (int i = 0; i < n; ++i)
		{
			if (num_of_two > 0)
			{
				num_of_two--;
				m -= 2;
				cout << 11;
			}
			else
			{
				cout << 1;
				m--;
			}
				
			cout << 0;
		}
		
		if (m == 2)
			cout << 11;
		else if (m == 1)
			cout << 1;
		return 0;
	}
}