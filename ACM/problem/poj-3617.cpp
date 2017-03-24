#include <iostream>
#include <stdio.h>

using namespace std; 

const int MAX_N = 2000 + 5;
int N;
char S[MAX_N];
int main() {
	cin >> N;
	for (int i =0; i < N; i++) {
		cin >> S[i];
	}

	int a = 0, b = N - 1, count = 0; 
	while (a <= b) {
		bool left = false;
		for (int i = 0; a + i <= b - i; i++) {
			if (S[a + i] < S[b - i]) {
				count++;
				left = true;
				break;
			} else if (S[a + i] > S[b - i]) {
				count++;
				left = false;
				break;
			}
		}

		if (left) putchar(S[a++]);
		else putchar(S[b--]);
		if(count % 80 == 0) putchar('\n');
	}
	return 0;
}