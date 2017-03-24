#include <stdio.h>
#include <string.h>

using namespace std;
const long long int MOD = 1e9 + 7;
long long int M[510];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long int n, m;
        scanf("%lld %lld", &n, &m);
        memset(M, 0, sizeof(M));
        for (int i = 0; i < m; ++i) {
            scanf("%lld", &M[i]);
        }
        
        long long int array[4] = { 0 };
        array[0] = 1;
        array[1] = 1;
        array[2] = 1;
        int index = 0;
        long long int last = 0;
        for (long long int i = 1ll; i <= n; ++i) {
            last = array[0];
            if (M[index] == i) {
                index++;
                last = 0;
            }
            array[0] = (array[1] + last) % MOD;
            array[1] = (last + array[2]) % MOD;
            array[2] = (last) % MOD;
        }
        printf("%lld\n", last);
    }
    return 0;
}