#include <stdio.h>
#include <algorithm>

using namespace std;

const int MAX_N = 10000 + 10;
const int MAX_D = 1000000 + 10;
const int INF = 0x3fffffff;
int N, ML, MD;
int AL[MAX_N], BL[MAX_N], AD[MAX_N], BD[MAX_N], DL[MAX_D], DD[MAX_D];
int d[MAX_N];

int main() {
	scanf("%d%d%d", &N, &ML, &MD);
	for (int i = 0; i < ML; ++i) {
		scanf("%d%d%d", &AL[i], &BL[i], &DL[i]);
		AL[i]--; BL[i]--;
	}
	for (int i = 0; i < MD; ++i) {
		scanf("%d%d%d", &AD[i], &BD[i], &DD[i]);
		AD[i]--; BD[i]--;
	}

	fill(d, d + N, INF);

	d[0] = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j + 1 < N; ++j) {
			if (d[j + 1] < INF) 
				d[j] = min(d[j], d[j + 1]);
		}

		for (int j = 0; j < ML; j++) {
			if (d[AL[j]] < INF) 
				d[BL[j]] = min(d[BL[j]], d[AL[j]] + DL[j]);
		}

		for (int j = 0; j < MD; j++) {
			if (d[BD[j]] < INF) 
				d[AD[j]] = min(d[AD[j]], d[BD[j]] - DD[j]);
		}
	}

	int res = d[N - 1];
	if (d[0] < 0) {
		printf("-1\n");
	} else if (res == INF) {
		printf("-2\n");
	} else {
		printf("%d\n", res);
	}
	return 0;
}