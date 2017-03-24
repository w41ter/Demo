#include <cstdio>
#include <algorithm>

using namespace std;

const int oo = 0x7fffff;
const int N = 1e5 + 5;
int maxv[2*N], minv[2*N], sumv[2*N], addv[2*N];
int _sum, _min, _max;

void maintain(int o, int l, int r)
{
	int lc = o << 1, rc = (o << 1) + 1;
	maxv[o] = minv[o] = sumv[o] = 0;
	if (r > l)
	{
		maxv[o] = max(maxv[lc], maxv[rc]);
		minv[o] = min(minv[lc], minv[rc]);
		sumv[o] = sumv[lc] + sumv[rc];
	}
	maxv[o] += addv[o];
	minv[o] += addv[o];
	sumv[o] += addv[o] * (r - l + 1);
}

int ul, ur, add;
void update(int o, int l, int r)
{
	int lc = o << 1, rc = (o << 1) + 1;
	if (ul <= l && ur >= r)
		addv[o] += add;
	else
	{
		int mid = l + (r - l >> 1);
		if (ul <= mid)
			update(lc, l, mid);
		if (ur > mid)
			update(rc, mid + 1, r);
	}
	maintain(o, l, r);
}

void query(int o, int l, int r, int add)
{
	if (ul <= l && ur >= r)
	{
		_max = max(_max, maxv[o] + add);
		_min = min(_min, minv[o] + add);
		_sum = _sum + sumv[o] + add * (r - l + 1);
	}
	else
	{
		int mid = l + (r - l >> 1);
		if (ul <= mid)
			query(o << 1, l, mid, add + addv[o]);
		if (ur > mid)
			query((o << 1) + 1, mid + 1, r, add + addv[o]);
	}
}

