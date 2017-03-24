#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <fstream>
#include <queue>
#include <map>

using namespace std;

//#define LOACLFILE 

const int N = 1e3 + 10;
map<string, int> __index;
map<int, string> name;
int parent[N], vis[N];

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
		int p, c;
		string strparent, strchild;
		cin >> strparent >> strchild;
		if (__index.count(strparent) == 0) 
		{
			p = __index[strparent] = __index.size();
			//cout << "Find Root Parent " << strparent << " index is " << p << endl;
			name[p] = strparent;
			parent[p] = -1;
		}
			
		p = __index[strparent];
		c = __index[strchild] = __index.size();
		//cout << '\t' << strchild << " index is " << c << " and father " << strparent << " index is " << p << endl;
		name[c] = strchild;
		parent[c] = p;
	}
	cin >> n;
	while (n--)
	{
		memset(vis, 0, sizeof(vis));
		string child1, child2;
		cin >> child1 >> child2;
		
		if (child1 == child2)
		{
			cout << child1 << endl;
			continue;
		}			
		//cout << "find child 1 " << child1 << endl;
		int p;
		if (__index.count(child1) == 0)
		{
			cout << -1 << endl;
			continue;
		}
		p = __index[child1];
		while (p != -1)
		{
			//cout << "\tFind " << name[p] << endl;
			vis[p] = 1;
			p = parent[p];
		}
		
		//cout << "find child 2 " << child2 << endl;
		
		if (__index.count(child2) == 0)
		{
			cout << -1 << endl;
			continue;
		}
		p = __index[child2];
		while (p != -1 && !vis[p])
		{
			//cout << "\tFind " << name[p] << endl;
			p = parent[p];
		}
			
		if (p == -1) 
			cout << -1 << endl;
		else 
			cout << name[p] << endl;
	}
	
	return 0;
}