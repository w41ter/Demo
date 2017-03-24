#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

#define LOACLFILE 
long long int sum[1005][6][1<<10];
int cnt[11];

int main()
{
	std::ios::sync_with_stdio(false);
	
	#ifdef LOACLFILE
	std::ifstream in("1.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
	#endif

	cnt[0] = 1;
	for (int i = 1; i < 11; ++i)
		cnt[i] = cnt[i-1] << 1;
	int n, m;
	cin >> n >> m;
	int largest = 1 << 2*m-1;
	for (int i = n; i > 0; ++i)
	{
		for (int j = m; j > 0; ++j)
		{
			for (int s = largest-1; s >= 0; ++s)
			{
				if (cnt[j]&s && j < m)
					sum[i][j][s] = sum[i][j+1][s];
				else 
			}
		}
	}
	return 0;
}