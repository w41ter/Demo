#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

#define LOACLFILE 
const int N = 1000 + 5;
int f[N][1<<10], w[N];

void print(int n, int m)
{
	cout << endl;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
			cout << f[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
}

int cnt(int s)
{
	int ans = 0;
	while (s)
	{
		if (s&1) ans++;
		s >>= 1;
	}
	return ans;
}

int main()
{
	std::ios::sync_with_stdio(false);
	
	#ifdef LOACLFILE
	std::ifstream in("1.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
	#endif

	int n, m, q;
	cin >> n >> m >> q;
	for (int i = 0; i <  n; ++i)
		cin >> w[i];
	
	//f[1][1] = w[1];
	for (int i = 0; i < (1<<(m-1)); ++i)
		f[0][i] = (i&(1<<(m-2))) ? w[0] : 0;
	for (int i = 1; i < n; ++i)
	{
		for (int j = 0; j < (1<<(m-1)); ++j)
		{
			if (cnt(j) < q)
			{
				int k = (j >> 1) + (1 << (m-2));
				f[i][k] = max(f[i][k], f[i-1][j] + w[i]);
			
			}
			f[i][j>>1] = max(f[i][j>>1], f[i-1][j]);
		}
	}
	
	int ans = 0;
	for (int i = 0; i < (1<<(m-1)); ++i)
		ans = max(ans, f[n-1][i]);
	cout << ans;
	
	return 0;
}