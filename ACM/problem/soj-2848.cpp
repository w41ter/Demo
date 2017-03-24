#include <iostream>
#include <algorithm>
using namespace std;
#define MAX_N 50000 + 16
int L, N, M;
int D[MAX_N];

bool C(int d) {
	int last = 0;
	for (int i = 1; i < N - M; ++i) {
		int current = last + 1;
		while (current < N && D[current] - D[last] < d)	
			++current;
		if (current == N)	
			return false;
		last = current;		
	}
	return true;
}

int main() {
	while (cin >> L >> N >> M) {
		for (int i = 1; i <= N; ++i) 
			cin >> D[i];
		++N;	
		D[N++] = L; 
		sort(D, D + N);
		int lb = 0, ub = L + 1;
		while (ub - lb > 1) {
			int mid = lb + (ub - lb) / 2;
			if (C(mid)) {
				lb = mid;
			} else {
				ub = mid;
			}
		}
		cout << lb << endl;
	}
	return 0;
}