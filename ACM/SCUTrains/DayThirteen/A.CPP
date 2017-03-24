#include <iostream>
#include <cstring>

using namespace std;

const int N = 1e5 + 4;
int d[N], ans;
int main()
{
	std::ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> d[i];
		if (d[i] == i)
			ans++;
	}
		
	bool flag = false;
	for (int i = 0; i < n; ++i)
	{
		if (i != d[i])
		{
			if (d[d[i]] == d[i])
				continue;
			else if (d[d[i]] == i)
			{
				ans += 2; 
				flag = false;
				break;
			}
			else if (!flag)
			{
				flag = true;
				continue;
			}
		}
	}
	if (flag) ans++;
	cout << ans;
	
	return 0;
}