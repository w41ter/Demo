#include <cstdio>
#include <algorithm>

using namespace std;

const int oo = 0x7fffff;
const int N = 1e5 + 5;
long int range[N], tree[4 * N];
long int r_max[4 * N], r_min[4 * N];

int rql, rqr, rp, rv;

int query_max(int o, int l, int r)
{
	//printf("%d %d %d\n %d %d \n", o, l, r, rql, rqr);
	int mid = l + ((r - l) >> 1), ans = 0;
	if (rql <= l && r <= rqr)
		return r_max[o];
	if (rql <= mid)
		ans = max(ans, query_max(o << 1, l, mid));
	if (rqr > mid)
		ans = max(ans, query_max((o << 1) + 1, mid + 1, r));
	return ans;
}

int query_min(int o, int l, int r)
{
	int mid = l + ((r - l) >> 1), ans = oo;
	if (rql <= l && r <= rqr)
		return r_min[o];
	if (rql <= mid)
		ans = min(ans, query_min(o << 1, l, mid));
	if (rqr > mid)
		ans = min(ans, query_min((o << 1) + 1, mid + 1, r));
	return ans;
}

void update(int o, int l, int r)
{
	int mid = l + ((r - l) >> 1);
	if (l == r)
		r_min[o] = r_max[o] = rv;
	else 
	{
		if (rp <= mid)
			update(o << 1, l, mid);
		else
			update((o << 1) + 1, mid + 1, r);
		
		r_min[o] = min(r_min[o << 1], r_min[(o << 1) + 1]);
		r_max[o] = max(r_max[o << 1], r_max[(o << 1) + 1]);
	}
}

int main()
{
	int n, c, b;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &c);
		rp = i + 1;
		rv = c;
		update(1, 1, n);
	}
	
	scanf("%d %d", &c, &b);
	rql = c;
	rqr = b;
	int max = query_max(1, 1, n);
	int min = query_min(1, 1, n);
	printf("max=:%d min=:%d max-min=:%d", max, min, max - min);

	return 0;
}
