#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

//#define LOACLFILE 
const int N = 5e4 + 10;
int str1[N], str2[N];
int n, m;

void cmd1(int i, int j, int c)
{
	for (int k = i-1; k < j; ++k)
	{
		str1[k] = c;
		//cout << str1[k]<<k;
	}
	//cout << endl;
}

void cmd2(int i, int j, int c)
{
	for (int k = i-1; k < j; ++k)
	{
		str1[k] += c;
		str2[k] %= 26;
	}
}

void cmd3(int k) 
{
	if (k < n - k)
	{
		for (int i = 0; i < k; ++i)
			str2[i] = str1[i];
		for (int i = 0; i < n - k; ++i)
			str1[i] = str1[k + i];
		for (int i = 0; i < k; ++i)
			str1[i + n - k] = str2[i];
	}
	else 
	{
		for (int i = k; i < n; ++i)
			str2[i] = str1[i];
		for (int i = k - 1; i >= 0; --i)
			str1[i + n - k] = str1[i];
		for (int i = 0; i < n-k; ++i)
			str1[i] = str2[k + i];
	}
}

void cmd4(int i, int j)
{
	i--;
	for (int k = 1; i < j; ++i, ++k)
	{
		str1[i] += k;
		str1[i] %= 26;
	}
}

int main()
{
	std::ios::sync_with_stdio(false);
	
	#ifdef LOACLFILE
	std::ifstream in("1.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
	#endif
	
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
	{
		char c;
		cin >> c;
		str1[i] = c - 'A';
	}
	while (m--)
	{
		char cmd[10];
		int key, i, j; char c;
		cin >> cmd >> key;
		switch (key)
		{
			case 1:
			{
				cin >> i >> j >> c;
				cmd1(i, j, c - 'A');
			}
			break;
			case 2:
			{
				cin >> i >> j >> key;
				cmd2(i, j, key);
			}
			break;
			case 3:
			{
				cin >> i;
				cmd3(i);
			}
			break;
			case 4:
			{
				cin >> i >> j;
				cmd4(i, j);
			}
			break;
		}
		// for (int i = 0; i < n; ++i)
			// cout << char(str1[i] + 'A');
		// cout << endl;
	}
	for (int i = 0; i < n; ++i)
		cout << char(str1[i] + 'A');
	return 0;
}