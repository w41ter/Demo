#include <iostream>
#include <cstdio>
#include <cstring>
#define MAXN 100100

using namespace std;
long long Q, M, T, ans, a[MAXN], op[MAXN], pnum[MAXN], queue[MAXN], q[MAXN];
int _begin, _end;

long long int top() { return queue[_begin];}
void pop() { _begin++;}
void push(int pos, long long int value) { q[_end] = pos, queue[_end++] = value;}

long long int multi() { 
    long long result = 1; 
    for (int i = _begin; i < _end; ++i) result = (result * queue[i]) % M;
    return result;
}

void remove(int i) { 
    for (int j = _begin; j < _end;  ++j)
    {
        if (q[j] == i)
        {
            q[j] = q[_begin];
            queue[j] = queue[_begin];
            pop();
            return;
        }
    }
}

int main()
{
    cin >> T;
    for(int cas=1;cas<=T;cas++)
    {
        scanf("%I64d %I64d",&Q,&M);
        pnum[0] = a[0] = 1;
        _begin = _end = 0;

        printf("Case #%d:\n",cas);
        for(int i=1;i<=Q;i++)
        {
            scanf("%I64d %I64d",&op[i],&a[i]);
            if (op[i] == 2) op[a[i]] = 3;
        }
        
        for(int i=1;i<=Q;i++)
        {
            if (op[i] == 1)
                pnum[i] = (pnum[i-1] * a[i]) % M;
            else 
                pnum[i] = (pnum[i-1]);
        }

        ans = 1;
        for (int i = 1; i <= Q; ++i)
        {
            if (op[i] == 3) 
            {
                push(i, a[i]);
                ans = multi();
            }
            else if (op[i] == 2)
            {
                remove(a[i]);
                ans = multi();
            }
            pnum[i] = (pnum[i] * ans) % M;
        }
        for (int i = 1; i <= Q; ++i)
            printf("%I64d\n", pnum[i]);
    }
    return 0;
}