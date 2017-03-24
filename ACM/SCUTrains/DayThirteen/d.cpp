#include <iostream>
#include <cstring>

using namespace std;

int a, b, c, c1, c2, c3;

int main()
{
	std::ios::sync_with_stdio(false);
	cin >> a >> b >> c;
	c1 = (a + b - c) / 2;
	c2 = (b + c - a) / 2;
	c3 = (a + c - b) / 2;
	if (c1 < 0 || c2 < 0 || c3 < 0 || (c1 + c2 + c3) <= 0 || (a + b + c) % 2 != 0)
	{
		cout << "Impossible";
		return 0;
	}
	else
	{
		cout << c1 << ' ';
		cout << c2 << ' ';
		cout << c3 << ' ';
		return 0;
	}
}