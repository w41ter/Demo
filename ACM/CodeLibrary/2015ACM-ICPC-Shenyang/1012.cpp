#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MOD = 530600414;
long long int sum[201315][2];
long long int num[201315];
long long int data[201315];
long long int length[201315];

void numer(int n) 
{
	length[3] = 3;
	length[4] = 5;

	sum[3][0] = 0;
	sum[3][1] = 3;
	sum[4][0] = 2;
	sum[4][1] = 3;

	num[3] = 1; 
	num[4] = 1;
	for (int i = 5; i < n; ++i) {
		sum[i][0] = (sum[i - 1][0] + sum[i-2][0] + (num[i - 1] * length[i-2]) %MOD) % MOD;
		sum[i][1] = (sum[i - 1][1] + sum[i-2][1] + (num[i - 2] * length[i-1]) %MOD) % MOD;

		data[i] = (sum[i-1][0] * num[i-2]) % MOD;
		data[i] = (data[i] + (sum[i-2][1] * num[i-1]) % MOD) % MOD;
		data[i] = (data[i] + data[i-2]) % MOD;
		data[i] = (data[i] + data[i-1]) %MOD;
		length[i] = (length[i-1] + length[i-2]) % MOD;
		num[i] = (num[i-1] + num[i-2]) % MOD;
	}
}

int main() {
	numer(201315);
	int T;
	scanf("%d", &T);
	int _case = 0;
	while (++_case <= T) {
		int i = 0;
		scanf("%d", &i);
		printf("Case #%d: %I64d\n", _case, data[i]);
	}
	return 0;
}