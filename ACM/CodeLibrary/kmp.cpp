#include <iostream>
#include <cstring>

using namespace std;

int f[123];

void getFail(const char *p)
{
	int m = strlen(p);
	f[0] = 0; f[1] = 0;
	for (int i = 1; i < m; ++i)
	{
		int j = f[i];
		while (j && p[i] != p[j]) j = f[j];
		f[i + 1] = p[i] == p[j] ? j + 1 : 0;
	}
}

void find(const char *T, const char *P)
{
	int n = strlen(T), m = strlen(P);
	getFail(P);
	int j = 0;
	for (int i = 0; i < n; ++i)
	{
		while (j && P[j] != T[i]) j = f[j];
		if (P[j] == T[i]) j++;
		if (j == m) cout << i - m + 1;
	}
}

int main()
{
	char *sz = "a1a1a1aasdfasdfasdf";
	char *file = "aa";
	int f[123];
	find(sz, file);
	return 0;
}

