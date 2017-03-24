#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <fstream>
#include <queue>
#include <map>

using namespace std;

//#define LOACLFILE 

const int N = 1e5 + 10;
int p[N];
map<string, int> name_map;

void init()
{
	for (int i = 0; i < N; ++i)
		p[i] = i;
}

int find(int a)
{
	int x = a;
	while (x != p[x]) x = p[x];
	
	int y;
	while (a != x) y = p[a], p[a] = x, a = y;
	return x;
}

void _union(int a, int b)
{
	int x = find(a), y = find(b);
	//cout << "Union " << x << " and " << y << endl;
	if (x == y) return ;
	p[x] = y;
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
	int n;
	cin >> n;
	while (n--)
	{
		int op;
		string name1, name2;
		cin >> op >> name1 >> name2;
		if (name_map.count(name1) == 0) name_map[name1] = name_map.size();
		if (name_map.count(name2) == 0) name_map[name2] = name_map.size();
		int a = name_map[name1], b = name_map[name2];
		//cout << a << " " << b << endl;
		if (op == 1) cout << (find(a) == find(b) ? "yes" : "no") << endl;
		else _union(a, b);
		
		//cout << "Begin:" << endl;
		//for (int i = 0; i < 5; ++i)
		//	cout << "\tpre[i] = " << p[i] << endl;
		//cout << "end\n";
	}
	
	return 0;
}