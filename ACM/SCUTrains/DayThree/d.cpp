#include <iostream>
#include <set>

using namespace std;

const int N = 1005;
char map[N][N];
int n, m, flag;
set<int> s;

int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> map[i];
		
	
	for (int i = 0; i < n; i++)
	{
		int b = 0, e = 0;
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] == 'G') 
				b = j;
			if (map[i][j] == 'S')
				e = j;
		}
		if (b < e)
			s.insert(e - b);
		else 
			flag = 1;
	}
	if (flag != 1)
		cout << s.size() << endl;
	else
		cout << -1 << endl;
	return 0;
}