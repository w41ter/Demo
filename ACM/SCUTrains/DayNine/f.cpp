#include <cstdio>
#include <iostream>

#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5+5;
char str[N];
char a, b;
int k, ans;

int main()
{
	scanf("%s%d", str, &k);
	int len = strlen(str);
	
	while (k--)
	{
		cin >> a >> b;
		for (int i = 0; i < len; ++i)
		{
			int l = 0, r = 0;
			while (str[i] == a || str[i] == b)
			{
				if (str[i] == a) l++;
				else if (str[i] == b) r++;
				i++;
			}
			ans += min(l, r);
		}
	}
	printf("%d", ans);
	return 0;
}