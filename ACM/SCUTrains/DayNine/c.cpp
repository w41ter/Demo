#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

const int mod = 1e9 + 7;

char s[101];
int f[101][101 * 26];

int main() 
{
	f[0][0] = 1;
	for (int i = 0; i < 100; ++i)
		for (int j = 0; j < 100 * 26; ++j)
			if (f[i][j] > 0)
			{
				for (int k = 0; k < 26; ++k)
				{
					f[i + 1][j + k] += f[i][j] % mod;
					f[i + 1][j + k] %= mod;
				}
			}
	
	int t = 0;
	char s[110];
	scanf("%d", &t);
	while (t--)
	{
		scanf("%s", s);
		int len = strlen(s); 
		int sum = 0;
		for(int i = 0; i < len; i++)
		{
		  sum += s[i] - 'a';                 
		}
		printf("%d\n", f[len][sum] - 1);       
	}
	return 0;
}