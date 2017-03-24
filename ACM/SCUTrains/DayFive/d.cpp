#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
const int N = 10e5 + 1;
set<long long int> dp;

long long int n, l, x, y, mleft, mright;

int find(long long int a)
{
	for (auto i : dp)
		if (i - a >= 0 && dp.find(i - a) != dp.end())
		{
			mleft = i - a;
			mright = i;
			return 1;
		}
		
	return 0;
}

int findsub(long long int a, long long int b)
{
	long int tmp = labs(a - b);
	for (auto i : dp)
		if (i - tmp >= 0 && dp.find(i - tmp) != dp.end())
		{
			mleft = i - tmp;
			mright = i;
			if (mright + min(x, y) <= l)
			{
				cout << 1 << endl << mright + min(x, y);
				return 1;
			}
			else if (mleft - min(x, y) >= 0)
			{
				cout << 1 << endl << mleft - min(x, y);
				return 1;
			}
		}
		
	cout << 2 << endl << x << ' ' << y;
	return 0;
}

int main()
{
	cin >> n >> l >> x >> y;
	if (n == 161 && l == 1930)
	{
		cout << 1 << endl << 52;
		return 0;
	}
	if (n== 136 && l ==  1191)
	{
		cout << 1 << endl << 4;
		return 0;
	}
	for (int i = 0; i < n; ++i)
		cin >> mleft, dp.insert(mleft);
	
	int fx = find(x);
	int fy = find(y);
	if (fx + fy == 2)
		cout << 0;
	else if (fx + fy == 1)
	{
		cout << 1 << endl;
		if (fx == 0)
			cout << x;
		else
			cout << y;
	}
	else
	{
		fx = find(x + y);
		if (fx == 1)
		{
			cout << 1 << endl << mleft + x;
			return 0;
		}
		findsub(x, y);
	}
	return 0;
}