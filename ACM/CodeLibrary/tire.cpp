#include <iostream>
#include <cstring>

using namespace std;

const int MAXNODE = 0xfff;
const int SIGMA_SIZE = 26;

class Tire
{
public:
	
	int ch[MAXNODE][SIGMA_SIZE];
	int val[MAXNODE];
	
	int sz;
	//void init() {sz = 1;}
	Tire() {sz = 1; memset(ch[0], 0, sizeof(ch[0]));}
	int idx(char c) { return c - 'a';}
	
	void insert(const char *s, int v)
	{
		//printf(s);
		//return ;
		int u = 0, n = strlen(s);
		for (int i = 0; i < n; ++i)
		{
			int c = idx(s[i]);	// first
			if (ch[u][c] == 0)
			{
				memset(ch[sz], 0, sizeof(ch[sz]));
				ch[u][c] = sz;
				val[sz] = 0;
				sz++;
			}
			u = ch[u][c];
		}
		val[u] = v;
	}
	
	int search(const char *s)
	{
		int u = 0, n = strlen(s);
		for (int i = 0; i < n; ++i)
		{
			int c = idx(s[i]);
			if (ch[u][c] == 0)
				return 0;
			u = ch[u][c];
		}
		return val[u];
	}
};

int main()
{
	char *test[] = { "asdfgghhh", "szie", "abcdefg", "maochuan", "first" };
	
	struct Tire tire;
	for (int i = 0; i < 5; ++i)
		tire.insert(test[i], i + 1);
	
	cout << "Find maochuan:" << tire.search("maochuan") << endl;
	cout << "Find maochuan1:" << tire.search("maochuan1") << endl;
	cout << "Find first:" << tire.search("first") << endl;
	cout << "Find szie2:" << tire.search("szie2") << endl;
	cout << "Find f:" << tire.search("asdfgghhh") << endl;
	
	return 0;
}
