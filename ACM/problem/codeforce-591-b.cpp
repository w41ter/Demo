#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAX_N = 2000000 + 10;
int N, M;
char name[MAX_N];
char dp[26];

void print() {
	for (int i = 0; i < N; ++i) {
		putchar(dp[name[i] - 'a']);
	}
	putchar('\n');
}

int main() {
	for (int i = 0; i < 26; ++i) 
		dp[i] = 'a' + i;
	cin >> N >> M >> name;
	//print();
	for (int i = 0; i < M; ++i) {
		char a, b;
		cin >> a >> b;
		for (int j = 0; j < 26; ++j) {
			if (dp[j] == a)
				dp[j] = b;
			else if (dp[j] == b)
				dp[j] = a;
		}
		//print();
	}
	for (int i = 0; i < N; ++i) {
		putchar(dp[name[i] - 'a']);
	}
	putchar('\n');
	return 0;
}

