#include <iostream>
#include <cstring>

using namespace std;

long long int _max, a[101], ans, n;

int gcd(int a,int b)
{
    int r;
    while(b>0)
    {
         r=a%b;
         a=b;
         b=r;
    }
    return a;
}

int main()
{
	std::ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
		if (_max < a[i])
			_max = a[i];
	}
	
	ans = gcd(a[0], a[1]);
	for (int i = 2; i < n; ++i)
	{
		ans = gcd(ans, a[i]);
	}
	
	_max /= ans;
	if ((_max - n) % 2 == 1)
		cout << "Alice";
	else
		cout << "Bob";
	
	return 0;
}