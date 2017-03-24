#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

//#define LOACLFILE 
const int N = 500 + 5;
const int M = 1e5 + 5;
int need[N], value[N], f[M];

int main()
{
	std::ios::sync_with_stdio(false);
	
	#ifdef LOACLFILE
	std::ifstream in("1.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
	#endif

	int n, m;
	cin >> n >> m;
	// for (int i = 0; i < n; ++i)
		// cin >> need[i] >> value[i];
	
	// for (int i = 0; i < n; ++i)
		// for (int j = m; j >= need[i]; --j)
			// f[j] = max(f[j], f[j - need[i]] + value[i]);
	
	int ne, va;
	for (int i = 0; i < n; ++i)
	{
		cin >> ne >> va;
		for (int j = m; j >= ne; --j)
			f[j] = max(f[j], f[j - ne] + va);
	}
	cout << f[m];
	
	return 0;
}