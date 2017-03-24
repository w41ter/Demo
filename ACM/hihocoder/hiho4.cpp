#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

//#define LOACLFILE 

const int N = 1e6 + 10;
char str[N];
int ch[N][26];
int val[N], last[N], fail[N];
	
class ACMachine
{
public:
	int sz;
	int idx(char c) { return c - 'a'; }
	void init() { sz = 1; memset(ch[0], 0, sizeof(ch[0])); }
	void insert(const char *str)
	{
		int len = strlen(str), u = 0;
		for (int i = 0; i < len; ++i)
		{
			int c = idx(str[i]);
			if (!ch[u][c])
			{
				memset(ch[sz], 0, sizeof(ch[sz]));
				ch[u][c] = sz++;
			}
			u = ch[u][c];
		}
		val[u]++;
	}
	
	bool find(const char *str)
	{
		int len = strlen(str);
		int j = 0;
		for (int i = 0; i < len; ++i)
		{
			int c = idx(str[i]);
			while (j && !ch[j][c]) j = fail[j];
			j = ch[j][c];
			if (val[j] || last[j]) return true;
		}
		return false;
	}
	
	void getfail()
	{
		queue<int> q;
		fail[0] = 0;
		for (int c = 0; c < 26; c++)
		{
			int u = ch[0][c];
			if (u) { fail[u] = 0; q.push(u); last[u] = 0; }
		}
		while (!q.empty())
		{
			int r = q.front(); q.pop();
			for (int c = 0; c < 26; ++c)
			{
				int u = ch[r][c];
				if (u == 0) continue;
				q.push(u);
				int v = fail[r];
				while (v && !ch[v][c]) v = fail[v];
				fail[u] = ch[v][c];
				last[u] = val[fail[u]] ? fail[u] : last[fail[u]];
			}
		}
	}
};

int main()
{
	std::ios::sync_with_stdio(false);
	
	#ifdef LOACLFILE
	std::ifstream in("1.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
	#endif

	ACMachine machine;
	machine.init();
	
	int n;
	cin >> n;
	while (n--)
	{
		cin >> str;
		machine.insert(str);
	}
	
	cin >> str;
	machine.getfail();
	if (machine.find(str)) cout << "YES";
	else cout << "NO";
	
	return 0;
}