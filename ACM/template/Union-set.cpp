int parent[MAX_N];

int union_set_init(int n) {
	for (int i = 0; i < n; ++i) parent[i] = i;
}

int union_set_find(int x) {
	if (parent[x] == x) 
		return x;
	else 
		return parent[x] = union_set_find(parent[x]);
}

void union_two_set(int x, int y) {
	x = union_set_find(x);
	y = union_set_find(y);
	if (x != y)
		parent[x] = y;
}

bool union_set_same(int x, int y) {
	return union_set_find(x) == union_set_find(y);
}