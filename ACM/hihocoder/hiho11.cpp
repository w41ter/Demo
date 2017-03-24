#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

//#define LOACLFILE 

const int N = 1e5 + 10;
vector<int> point[N];
int vis[N], ans;

int dfs(int n)
{
	int first = 0, second = 0;
	//cout << "begin:" << n << endl;
	for (int i = 0; i < point[n].size(); ++i)
	{
		if (vis[point[n][i]]) continue;
		//cout << "I am Check point : " << n << " to " << point[n][i] << endl;
		vis[point[n][i]] = 1;
		int depth = dfs(point[n][i]) + 1;
		if (depth >= first) second = first, first = depth;
		else if (depth > second) second = depth;
		else continue;
		ans = max(ans, first + second);
	}
	//cout << "End Point :" << n << " " << first << " " << second << endl;
	return first;
}

int main()
{
	std::ios::sync_with_stdio(false);
	
	#ifdef LOACLFILE
	std::ifstream in("1.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
	#endif

	int n = 0, k; 
	cin >> n;
	k = n;
	while (k--)
	{
		int a, b;
		cin >> a >> b;
		point[a].push_back(b);
		point[b].push_back(a);
	}
	
	for (int i = 0; i <= n; ++i)
	{
		if (point[i].size() == 0) continue;
		//cout << "find : " << i << endl;
		vis[i] = 1;
		dfs(i);
		break;
	}
	cout << ans;
	
	return 0;
}