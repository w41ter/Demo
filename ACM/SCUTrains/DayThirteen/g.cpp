#include <iostream>
#include <cstring>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

const int N = 1e5 + 5;
long long int h[N], p[N], n, m, ans;

bool check(long long int x)
{
	int k = 0;
	for (int i = 0; i < n && k < m; ++i)
	{
		if (h[i] - p[k] > x) return false;
		long long int length = h[i];
		if (p[k] <= length)
		{
			length = max(length, x - (h[i] - p[k]) + p[k]);
            length = max(length, (x - (h[i] - p[k])) / 2 + h[i]);
		}
		else
		{
			length += x;
		}
		while (k < m && p[k] <= length) k++;
	}
	if (k < m) return false;
	else return true;
}

int main()
{
	std::ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		cin >> h[i];
	for (int i = 0; i < m; ++i)
		cin >> p[i];
	
	long long int left = 0, right = 1e12 + 5;
	while (left <= right)
	{
		long long int mid = left + ((right - left) >> 1);
		//bool state = check(mid);
		//cout << left << ' ' << mid <<' ' << right << ' ' << state << endl;
		if (check(mid))
			right = mid - 1, ans = mid;
		else
			left = mid + 1;
	}
	cout << ans;
	return 0;
}