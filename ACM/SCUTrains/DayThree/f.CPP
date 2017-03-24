#include <iostream>
#include <cmath>

using namespace std;
long long int sum, ans;
int n, x;

int main()
{
	cin >> n >> x;
	for (int i = 0; i < n; ++i)
	{
		int a = 0;
		cin >> a;
		sum += a;
	}
	ans = labs(sum) / x;
	if (labs(sum) % x != 0)
		ans++;
	cout << ans << endl;
}