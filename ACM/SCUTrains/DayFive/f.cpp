#include <iostream>

using namespace std;

const int N = 10e5 + 1;
int arr[N];
bool vis[N];

int main()
{
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++)
		arr[i] = i + 1, vis[i] = false;
	
	for (int i = 0; i < n; ++i)
	{
		if (vis[i])
			continue;
		
		vis[i] = true;
		
		cout << arr[i] << ' ';
		if (!vis[k] && k + 1 > 2)
		{
			cout << k + 1 << ' ';
			vis[k--] = true;
		}
	}
	return 0;
}