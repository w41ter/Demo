#include <cstdio>
#include <cstring>

using namespace std;

int m, n, result;
char map[100][100], c;
bool color[26];

bool cal(int x, int y)
{
	bool flag = false;
	if (x > 0 && map[x - 1][y] == c)	// up
		flag = true;
	if (x < n - 1 && map[x + 1][y] == c)
		flag = true;
	if (y > 0 && map[x][y - 1] == c)
		flag = true;
	if (y < m - 1 && map[x][y + 1] == c)
		flag = true;
	
	return flag;
}

int Slove()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] != '.' && map[i][j] != c && cal(i, j))
			{
				if (color[map[i][j] - 'A'])
					continue;
				color[map[i][j] - 'A'] = true;
				//printf("find character : %c\n", map[i][j]);
				result++;
			}
		}
	return result;
}

int main()
{
	memset(color, false, sizeof(color));
	
	scanf("%d%d %c", &n, &m, &c);
	for (int i = 0; i < n; i++)
		scanf("%s", map[i]);
	
	printf("%d", Slove());
	return 0;
}