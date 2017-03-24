#include <iostream>
#include <math.h>
using namespace std;
long long int n, ans;
long long int find(long long int i) { return (i & 1ll)? i : find(i >> 1); }
long long int pow(long long int i) { return i * i; }
int main() {
	while (cin >> n) {
		int N = log(n) / log(2ll);
		cout << N << endl;
		//long long int tmp = (n & 1ll) ? n + 1 : n;
		//ans = pow((tmp) >> 1);
		
		//for (long long int i = 2ll; i <= n; i += 2) {
		//	ans += find(i);
		//}
		//cout << ans << ' ' << (pow(tmp) + 2) / 3 << endl;
		//cout << log(1000000000ll) << endl;
	}
	return 0;
}