#include <cstdio>
#include <algorithm>

using namespace std;

const int oo = 0x7fffff;
const int N = 1e5 + 5;
int sumv[2*N], maxv[2*N], minv[2*N], set[2*N];
int _max, _min, _sum;

void maintain(int o. int l, int r)
{
	int lc = o << 1, rc = (o << 1) + 1;
	// minv[o] = maxv[o] = sumv[o] = 0;
	if (l < r)
	{
		minv[o] = min(minv[lc], mimv[rc]);
		maxv[o] = max(maxv[lc], maxv[rc]);
		sumv[o] = sumv[lc] + sumv[rc];
	}
	else if (setv[o] >= 0)
	{
		minv[o] = maxv[o] = sumv[o] = setv[o];
		setv[o] = -1;
	}
}

void pushdown(int o)
{
	if (setv[o] >= 0)
	{
		setv[o << 1] = setv[(o << 1) + 1] = setv[o];
		setv[o] = -1;
	}
}

int ul, ur, us;
void update(int o, int l, int r)
{
	if (ul <= l && ur >= r)
	{
		setv[o] = us;
	}
	else
	{
		pushdown(o);
		int mid = l + (r - l >> 1);
		if (mid >= l)
			update(o << 1, l, mid);
		else
			maintain(o, l, mid);
		if (mid < r)
			update((o << 1) + 1, mid + 1, r);
		else
			maintain(o, mid + 1, r);
	}
	maintain(o, l, r);
}

int ql, qr;
void query(int o, int l, int r)
{
	if (setv[o] >= 0)
	{
		_sum += setv[o] * (min(qr, r) - max(rl, l) + 1);
		_min = min(_min, setv[o]);
		_max = max(_max, setv[o]);
	}
	else if (ql <= l && qr >= r)
	{
		_sum += sumv[o];
		_min = min(_min, minv[o]);
		_max = max(_max, maxv[o]);
	}
	else
	{
		int mid = l + (r - l >> 1);
		if (l <= mid)
			query(o << 1, l, mid);
		if (r > mid)
			query((o << 1) + 1, mid + 1, r);
	}
}