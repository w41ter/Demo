#include <stdio.h>
#include <math.h>

#define MAX_N 110
#define Max(a, b) (a > b ? a : b)

struct Gangster { int t, p, s;} gangster[MAX_N];

int cmp(const void *a, const void *b) {
	return ((struct Gangster*)a)->t - ((struct Gangster*)b)->t;
}

int N, K, T, f[MAX_N];

int main() {
	while (scanf("%d %d %d", &N, &K, &T) != EOF) {
		for (int i = 0; i < N; ++i) 
			scanf("%d", &gangster[i].t);
		for (int i = 0; i < N; ++i) 
			scanf("%d", &gangster[i].p);
		for (int i = 0; i < N; ++i) 
			scanf("%d", &gangster[i].s);
		qsort(gangster, N, sizeof(gangster[0]), cmp);
		for (int i = 0; i < N; ++i) {
			if (gangster[i].t >= gangster[i].s) 
				f[i] = gangster[i].p;
			else {
				f[i] = -1;
				continue;
			}
			for (int j = 0; j < i; ++j) {
				if (abs(gangster[j].s - gangster[i].s) <= abs(gangster[j].t - gangster[i].t))
					f[i] = Max(f[i], f[j] + gangster[i].p);

			}
		}
		int ans = 0; 
		for (int i = 0; i < N; ++i) {
			ans = Max(ans, f[i]);  
        }  
        printf("%d\n", ans);  
	}
	return 0;
}