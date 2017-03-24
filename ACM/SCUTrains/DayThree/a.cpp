#include <iostream>

using namespace std;

int n, p, k;

int main()
{
	cin >> n >> p >> k;
	if (p < 1 || p > n)
		return 0;
	if (p-k > 1)
		cout << "<< ";
	for (int i = (p - k >= 1 ? p - k : 1); i <= p + k && i <= n; i++)
	{
		if (i == p)
			cout << "(" << i << ") ";
		else 
			cout << i << " ";
	}
	if (p + k < n)
		cout << ">>" ;
	return 0;
}