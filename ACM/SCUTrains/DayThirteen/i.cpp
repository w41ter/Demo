#include <iostream>
#include <cstring>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

const int N = 2e6 + 5;
char y[N], a[N];
int y123, a1, t1;

int main()
{
	std::ios::sync_with_stdio(false);
	int n = 0;
	cin >> n;
	cin >> y >> a;
	
	for (int i = 0; i < 2* n; ++i)
	{
		//cout << y[i];
		if (a[i] == y[i] && a[i] == '1') 
			t1++;
		if (y[i] == '1')
			y123++;
		if (a[i] == '1')
			a1++;
	}
	//cout << y123 << ' ' << a1 << ' ' << t1 << endl;
	y123 -= t1;
	a1 -= t1;
	if (t1 % 2 == 1)
		y123++;
	if (y123 < a1)
		a1 -= (a1 - y123) / 2 + (a1 - y123) % 2;


	if (y123 > a1)
		cout << "First";
	else if (y123 < a1) 
		cout << "Second";
	else
		cout << "Draw";
	//cout << y123 << ' ' << a1 << endl;
	return 0;
}