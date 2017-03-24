#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;

const int maxn=1e3+10;
int f[maxn],g[maxn];
void random(int t)
{

    int i,j,k,m,num=0;
    for(i=0;i<t;i++)f[i]=i;
    m=t;
    for(i=0;i<t;i++)
    {
        num=rand()%m;
        g[i]=f[num];
        f[num]=f[m-1];
        m--;
    }
}
int judge()
{
    int i,j,k=0;
    for(i=0;i<9;i++)
    {
        //printf("%c\n",e.c[i]);
        if(g[i]==0)continue;
        for(j=0;j<i;j++)
        {
            if(g[j]==0)continue;
            if(g[j]>g[i])k++;
        }
    }
    return k%2;
}
int main()
{
    freopen("test.txt","w",stdout);
    srand(time(NULL));
    int i,j,k,n;
    printf("2\n");
    for(i=0;i<10;i++)
    {
        random(9);
        k=judge();
        for(j=0;j<9;j++)
        {
            if(g[j]==0)
                printf("X");
            else
                printf("%d",g[j]);
        }
        printf("\n");
        do
        {
            random(9);
        }while(k!=judge());
        for(j=0;j<9;j++)
        {
            if(g[j]==0)
                printf("X");
            else
                printf("%d",g[j]);
        }
        printf("\n");
    }
}