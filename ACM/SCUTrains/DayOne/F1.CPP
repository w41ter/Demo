#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1200005;
int a[MAXN], prim[MAXN], hw[MAXN], p, q;

int judge(int k) {
	int len = 0;
	char c[10];
	while(k > 0) {
		c[len++] = char(k % 10 + '0');
		k /= 10;
	}
	for(int i = 0; i < len / 2; ++i)
		if(c[i] != c[len - i - 1]) 
			return 0;
	return 1;
}

int main() {
	for(int i = 1; i <= 1200000; ++i)
		hw[i] = hw[i - 1] + judge(i);
	scanf("%d%d", &p, &q);
	for(int i = 2; i <= sqrt(1200000); ++i) {
		if(!a[i])
			for(int j = i * 2; j <= 1200000; j += i) {
				a[j] = 1;
				prim[i] = 1;
			}
		prim[i] += prim[i - 1];
	}
	for(int i = sqrt(120000) + 1; i <= 1200000; ++i)
		prim[i] = prim[i - 1] + (!a[i]);
	for(int i = 1200000; i >= 0; --i)
		if(prim[i] <= double(hw[i] * p / q)) {
			printf("%d\n", i);
			return 0;
		}
	printf("Palindromic tree is better than splay tree\n");
	return 0;
}