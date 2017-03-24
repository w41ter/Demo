#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

//#define LOACLFILE 

const int PN = 1e4 + 10;
const int ON = 1e6 + 10;
char pstr[PN], ostr[ON];
int fail[PN];

void getfail(int len)
{
	fail[0] = fail[1] = 0;
	int j = 0;
	for (int i = 1; i < len; ++i)
	{
		j = fail[i];
		while (j && pstr[i] != pstr[j]) j = fail[j];
		fail[i + 1] = (pstr[i] == pstr[j] ? j + 1 : 0);
	}
}

int kmp()
{
	int len = strlen(ostr), m = strlen(pstr), count = 0;
	getfail(m);
	int j = 0;
	for (int i = 0; i < len; ++i)
	{
		while (j && pstr[j] != ostr[i]) j = fail[j];
		if (pstr[j] == ostr[i]) j++;
		if (j == m) count++;
	}
	return count;
}

int main()
{
	std::ios::sync_with_stdio(false);
	
	#ifdef LOACLFILE
	std::ifstream in("1.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
	#endif

	int n;
	cin >> n;
	while (n--)
	{
		cin >> pstr >> ostr;
		cout << kmp() << endl;
	}
	
	return 0;
}