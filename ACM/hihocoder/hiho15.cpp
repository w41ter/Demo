#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <fstream>
#include <queue>
#include <map>

using namespace std;

#define LOACLFILE

const int N = 1e5 + 10;
int p[N];
map<string, int> name_map;
map<int, string> index_map;

int color[N], ans[N], a;
vector<int> tree[N];
vector<int> query[N];
vector<int> query_pos[N];

void remove_point(int a, int b)
{
	for (auto i = query[a].begin(); i != query[a].end(); ++i)
	{
		if (*i == b)
		{
			query[a].erase(i);
			break;
		}
	}
}

int get_id(string &str)
{
	if (name_map.count(str) == 0)
	{
		int i = name_map[str] = name_map.size();
		//query_pos[n][i]cout << str << " position is : " << i << endl;
		index_map[i] = str;
	}

	return name_map[str];
}

void init()
{
	for (int i = 0; i < N; ++i) p[i] = i;
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
	p[y] = x;
}

void dfs(int n)
{
	color[n] = 1; 	// 灰色
	for (int i = 0; i < tree[n].size(); ++i)
	{
		dfs(tree[n][i]);
		_union(n, tree[n][i]);
	}
	for (int i = 0; i < query[n].size(); ++i)
	{
		int p = query[n][i], pos = query_pos[n][i];
		if (color[p] == 1) ans[pos] = p, a++;
		else if (color[p] == 2) ans[pos] = find(p), a++;
	}
	color[n] = 2; 	// 黑色
}

void lcs(int q)
{
	dfs(1);
	for (int i = 0; i < q; ++i) {
		cout << index_map[ans[i]] << endl;
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

	init();
	int n;
	cin >> n;
	while (n--)
	{
		string name1, name2;
		cin >> name1 >> name2;
		int id1 = get_id(name1), id2 = get_id(name2);
		tree[id1].push_back(id2);
	}

	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		string name1, name2;
		cin >> name1 >> name2;
		int id1 = get_id(name1), id2 = get_id(name2);
		query[id1].push_back(id2);
		query_pos[id1].push_back(i);
		query[id2].push_back(id1);
		query_pos[id2].push_back(i);
		ans[i] = 0;
	}

	lcs(n);

	return 0;
}
