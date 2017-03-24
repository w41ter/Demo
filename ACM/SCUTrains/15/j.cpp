#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	int n;
	while (cin >> n)
	{
		int ans = (n-1)*n/2 + 1 - (n-1)/2;
		for (int i = 0; i < n-1; ++i)
			ans += n*n - 2 * i;
		cout << ans << endl;
	}
	return 0;
}