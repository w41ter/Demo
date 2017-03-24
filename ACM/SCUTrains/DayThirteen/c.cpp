#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cstring>

using namespace std;

const int N = 200;
int dp[N][N], path[N][N];
char mp[2*N], s1[N], s2[N], virus[N];
char lcs[N];
bool vis[N][N];
int len1, len2, fail[2*N];

void init(char *find)
{
	int len = strlen(find);
	fail[0] = fail[1] = 0;
	for (int i = 1; i < len; ++i)
	{
		int j = find[i];
		while (j && find[i] != find[j]) j = fail[j];
		fail[i + 1] = (find[i] == find[j]) ? j + 1 : 0;
	}
}

bool kmp(char *source, char *find)
{
	int lens = strlen(source), lenf = strlen(find);
	int j = 0;
	for (int i = 0; i < lens; ++i)
	{
		while (j && source[i] != find[j]) j = fail[j];
		if (source[i] == find[j]) j++;
		if (j == lenf) return true;
	}
	return false;
}

void LCS()
{
	for (int i = 1; i <= len1; ++i)
		for (int j = 1; j <= len2; ++j)
		{
			if (s1[i-1] == s2[j-1])
			{
				dp[i][j] = dp[i-1][j-1] + 1;
				path[i][j] = 1;
			}
			else if (dp[i-1][j] > dp[i][j-1])
			{
				dp[i][j] = dp[i-1][j];
				path[i][j] = 2;
			}
			else if (dp[i-1][j] < dp[i][j-1])
			{
				dp[i][j] = dp[i][j-1];
				path[i][j] = 3;
			}
			else
			{
				dp[i][j] = dp[i][j-1];
				path[i][j] = 4;
			}
		}
		
	// for (int i = 0; i <= len1; ++i)
	// {
		// for (int j = 0; j <= len2; ++j)
			// cout << dp[i][j] << "(" << path[i][j] << ")   ";
		// cout << endl;
	// }
		
}

bool Trackback(int i, int j, int curlen, int maxlen)
{
	//if (vis[i][j]) return false;
	//vis[i][j] = true;
	bool state = false;
	//cout << "locate(" << i << ", " << j << ")" << endl;
	if (i == 0 || j == 0)
	{
		//if (kmp(lcs, virus)) state = false;
		for (int k = 0; k < maxlen; ++k)
			cout << lcs[k];
		cout << endl;
		state = false;
	}
	if (path[i][j] == 1)
	{
		//cout << "find one " << i << endl;
		lcs[--curlen] = s1[i-1];
		state = Trackback(i-1, j-1, curlen, maxlen);
	}
	else if (path[i][j] == 2)
	{
		state = Trackback(i-1, j, curlen, maxlen);
	}
	else if (path[i][j] == 3)
	{
		state = Trackback(i, j-1, curlen, maxlen);
	}
	else
	{
		state = Trackback(i-1, j, curlen, maxlen);
		state = Trackback(i, j-1, curlen, maxlen);
	}
	//vis[i][j] = false;
	return state;
}

void Output(int i, int j)
{
	if (i == 0 || j == 0)
		return ;
	int tmp = path[i][j];
	if (tmp == 1)
	{
		Output(i-1, j-1);
		cout << s1[i - 1];
	}
	else if (tmp == 2)
	{
		Output(i-1, j);
	}
	else
	{
		Output(i, j-1);
	}
}

int main()
{
	cin >> s1 >> s2 >> virus;
	len1 = strlen(s1);
	len2 = strlen(s2);
	init(virus);
	LCS();
	//Output(len1, len2);
	for (int i = dp[len1][len2]; i > 0; --i)
	{
		if (Trackback(len1, len2, i, i))
			return 0;
	}
	cout << 0;
	return 0;
}

