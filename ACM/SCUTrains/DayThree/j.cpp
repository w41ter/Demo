#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
#define MaxN 5555
const int maxn = 1000000;
bool flag[maxn+5];
int prime[maxn/3], TopPrime;
int a[MaxN], bad[MaxN], gtf[MaxN];
set <int> badSet;
map <int, int> memo;

void calc_prim(){
    for(int i = 2; i <= maxn; i ++){
        if(!flag[i]) prime[TopPrime++] = i;
        for(int j = 0; j < TopPrime && prime[j]*i <= maxn; j ++){
            flag[i*prime[j]] = 1;
            if(i%prime[j]==0) break;
        }
    }
}

int F(int s)
{
    if(s == 1) return 0;
    if(memo.find(s) != memo.end()) return memo[s];
    int k = 0, ans = 0;
    int num = s;
    while(prime[k]*prime[k] <= s)
    {
        if(s % prime[k] == 0)
        {
            int isbad = badSet.count(prime[k]);
            while(s%prime[k] == 0)
            {
                s/=prime[k];
                if(isbad)
                    ans--;
                else
                    ans++;
            }
        }
        k++;
    }
    if(s != 1)
    {
        if(badSet.count(s)) ans--;
        else ans++;
    }
    return memo[num] = ans;
}

int main()
{
//    freopen("data.in", "r", stdin);
    calc_prim();
    int n, m, G, cur, sum;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    for(int i = 0; i < m; i++)
    {
        scanf("%d", &bad[i]);
        badSet.insert(bad[i]);
    }
    G = a[0];
    sum = 0;
    for(int i = 0; i < n; i++)
    {
        int number = a[i];
        sum += F(number);
        G = __gcd(number, G);
        gtf[i] = F(G);
    }

    cur = 0;//the F() of gcd been cut before
    for(int i = n-1; i >= 0; i--)
    {
        if(gtf[i] + cur < 0)//!!!
        {
            sum -= (gtf[i] + cur)*(i+1);//!!!
            cur += (gtf[i] + cur)/(-1);
        }
    }
    printf("%d\n", sum);
    return 0;
}