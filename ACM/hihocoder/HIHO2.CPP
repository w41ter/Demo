#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

//#define LOACLFILE 

const int N = 1e6 + 10;
int node[N][26], l[N];
int sz;

int idx(char c) { return c - 'a'; }

void init()
{
	sz = 1;
	memset(node[0], 0, sizeof(node[0]));
}

void insert(const char *str)
{
	int len = strlen(str);
	int u = 0;
	for (int i = 0; i < len; ++i)
	{
		int c = idx(str[i]);
		if (!node[u][c]) 
		{
			memset(node[sz], 0, sizeof(node[sz]));
			node[u][c] = sz++;
		}
		u = node[u][c];
		l[u]++;
	}
}

int find(const char *str)
{
	int len = strlen(str);
	int u = 0;
	for (int i = 0; i < len; ++i)
	{
		int c = idx(str[i]);
		if (!node[u][c]) return 0;
		u = node[u][c];
	}
	
	return l[u];
}

int main()
{
	std::ios::sync_with_stdio(false);
	
	#ifdef LOACLFILE
	std::ifstream in("1.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
	#endif

	init();
	int t;
	cin >> t;
	while (t--)
	{
		string str;
		cin >> str;
		insert(str.c_str());
	}

	cin >> t;
	while (t--)
	{
		string str;
		cin >> str;
		cout << find(str.c_str()) << endl;
	}
	return 0;
}