#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=2000 + 100;
char a[N], b[N];
int la, lb, res;

int cmp(int i)
{
	int c = 0;
	for (int j = 0; j < lb; ++j, i++)
	{
		//printf("cmp %d %c %c\n", i, a[i], b[j]);
		if (i < 0)
			continue;
		else if (i >= la)
			break;
		else if (a[i] == b[j])
			c++;
	}
	return c;
}

int main()
{
	scanf("%s%s", a, b);
	
	la = strlen(a);
	lb = strlen(b);
	
	for(int i = 0 - lb + 1; i < la; i++)
	{
		int moves = cmp(i);
		if (res < moves)
			res = moves;
	}
	printf("%d", lb - res);
	return 0;
}

