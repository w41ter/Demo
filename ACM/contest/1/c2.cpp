#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int ans,n,k,t,g,h; 
int main() {
	scanf("%d%d", &n, &k);
	t = 0;
	ans = abs(n-k);
	g = k, h = -1; 
	while (g > 1) {
		if (h == -1) {
			if (g & 1) 
				h =(g >> 1) + 1, g >>= 1, t += 2; 
			else 
				g >>= 1, t++; 
		} else {
			if (g&1) 
				g = h >> 1; 
			else 
				g = g>> 1; 
			h = -1; 
			t++;
		}
		ans = min(ans , t + abs(n - g));
		if (h != -1) ans = min(ans, t + abs(n - h));
	}
	printf("%d\n" , ans);
}