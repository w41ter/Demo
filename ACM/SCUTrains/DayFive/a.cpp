#include <iostream>

using namespace std;

int a, b, c, ans;

int max(int a, int b)
{
	if (a > b)
		return a;
	else 
		return b;
}

int cal()
{
	int cur = 0;
	cur = a + b + c;
	ans = max(ans, cur);
	cur = a + b * c;
	ans = max(ans, cur);
	cur = a * b + c;
	ans = max(ans, cur);
	cur = a * b * c;
	ans = max(ans, cur);
	cur = (a + b) * c;
	ans = max(ans, cur);
	cur = a * (b + c);
	ans = max(ans, cur);
	return ans;
}

int main()
{
	cin >> a >> b >> c;
	cal();
	cout << ans;
	return 0;
}