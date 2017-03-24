#include <iostream>
#include <cstring>

using namespace std;

const int INF = 0xffff;
int dist[100][100];

int min(int left, int right)
{
	if (left < right)
		return left;
	else 
		return right;
}

void Floyd()
{
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

int main()
{
	memset(dist, INF, sizeof(dist));
	if ()
}