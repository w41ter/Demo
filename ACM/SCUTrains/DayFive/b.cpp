#include <iostream>
#include <cstdlib>
#include <queue>

using namespace std;

struct Tower
{
	int height;
	int position;
};

int cmp(const void *a, const void *b)
{
	return ((struct Tower*)b)->height - ((struct Tower*)a)->height;
}

const int N = 101;
struct Tower tower[N];
int n, k, sub;
queue<int> f, b;

int print()
{
	for (int i = 0; i < n; ++i)
	{
		cout << tower[i].height << ' ' << endl;
	}
	return 0;
}

int main()
{
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> tower[i].height;
		tower[i].position = i + 1;
	}
	qsort(tower, n, sizeof(Tower), cmp);
	sub = tower[0].height - tower[n-1].height;
	//print();
	for (int i = 0; i < k && tower[0].height - tower[n-1].height > 1; ++i)
	{
		tower[0].height--;
		f.push(tower[0].position);
		tower[n-1].height++;
		b.push(tower[n-1].position);
		qsort(tower, n, sizeof(Tower), cmp);
	}
	
	cout << tower[0].height - tower[n-1].height << ' ' << f.size() << endl;
	while (!f.empty())
	{
		cout << f.front() << ' ' << b.front() << endl;
		f.pop();
		b.pop();
	}
	return 0;
}