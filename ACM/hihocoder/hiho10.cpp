#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

//#define LOACLFILE 
char pre[30], mid[30];

void pre_order(char *pre, int lpre, char *mid, int lmid)
{
	if (lpre <= 0) return ;
	if (lpre == 1)
	{
		cout << pre[0];
		return ;
	}
	char c = pre[0];
	int i = 0;
	for (; i < lmid; ++i)
		if (mid[i] == c) break;
	pre_order(pre + 1, i, mid, i);
	pre_order(pre + i + 1, lpre - i - 1, mid + i + 1, lmid - i - 1);
	cout << c;
}

int main()
{
	std::ios::sync_with_stdio(false);
	
	#ifdef LOACLFILE
	std::ifstream in("1.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
	#endif

	cin >> pre >> mid;
	pre_order(pre, strlen(pre), mid, strlen(mid));
	return 0;
}