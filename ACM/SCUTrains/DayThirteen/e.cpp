#include <iostream>
#include <cstring>

using namespace std;

long long int a, b;

long long int cal(long long int a, long long int b)
{
	long long int ans = a / b;
	if (a % b != 0)
	{
		ans += cal(b, a % b);
	}
	return ans;
}

int main()
{
	std::ios::sync_with_stdio(false);
	cin >> a >> b;
	cout << cal(a, b);
	return 0;
}
