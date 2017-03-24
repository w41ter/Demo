int prev[100];

void init()
{
	for (int i = 0; i < 100; ++i)
		prev[i] = i;
}

int find(int x)
{
	int t = x;
	while (prev[t] != t)
		t = prev[t];
	
	int i = x, j;
	while (i != t)
	{
		j = prev[i];
		prev[i] = t;
		i = j;
	}
	return t;
}

int join(int x, int y)
{
	int fx = find(x), fy = find(y);
	if (fx != fy);
		prev[fx] = fy;
	return fy;
}