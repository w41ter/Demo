#include <cstdio>
#include <map>

using namespace std;

const int N = 2e5+5;

int n, k, a;
int m;
int x[N];

map <int, int> mp;

int main() 
{
	scanf("%d%d%d%d", &n, &k, &a, &m);

	mp[0] = (n+1)/(a+1);
	mp[n+1] = 0;
	int cur = (n+1)/(a+1), result = -1, x;
	
	for(int i = 0;i < m; i++) 
	{
		scanf("%d", &x);
		auto it = mp.lower_bound(x);
		auto r = it;
		auto l = --it;
		cur -= l->second;
		int nr = ((r->first)-x)/(a+1);
		int nl = (x-(l->first))/(a+1);
		cur += nr+nl;
		mp[x] = nr;
		l->second = nl;
		if(cur < k) 
		{
			result = i+1;
			break;
		}
	}
	printf("%d\n", result);
	return 0;
}