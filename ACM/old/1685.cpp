#include <stdio.h>
#include <string.h>

int dp[5050];
int s[5050];
int table[5050][1009];

int k, m;
int max = 0;

int min(int a, int b)
{
    return a &lt;= b ? a : b;
}

int squ(int  a)
{
    return a * a;
}

int slove(int total, int index)
{
    if (index &gt;= k) return 0;
    if (total &lt;= 0) return 0xffffff;
    if (table[total][index] &gt;= 0) return table[total][index];

    if (max &lt;= 0)
    {
        max++;
        table[total][index] = slove(total -1, index);
    }
    else
    {
        max--;
        int x = dp[total] + slove(total - 2, index+1);
        max++;

        max++;
        table[total][index] = min(x, slove(total - 1, index));
        max--;

        if (table[total][index] == x) max--;
        else max++;
    }

    return table[total][index];
}

int main()
{
    int t = 0;
    scanf("%d", &amp;t);

    while (t--)
    {
        scanf("%d %d", &amp;k, &amp;m);
        k += 8, max = 1;

        memset(dp, 0, sizeof(dp));
        memset(s, 0, sizeof(s));
        memset(table, -1, sizeof(table));

        for (int i = 0; i &lt; m; i++) scanf("%d", &amp;s[i]);
        for (int j = m - 1; j &gt; 0; j--) dp[j] = squ(s[j] - s[j - 1]);

        printf("%d\n", slove(m - 2, 0));
    }

    return 0;
}
