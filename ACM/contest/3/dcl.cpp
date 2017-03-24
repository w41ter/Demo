/* ***********************************************
Author        :kuangbin
Created Time  :2014/8/21 16:23:46
File Name     :09.cpp
************************************************ */

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int MaxM = 15*15+10+1000;
const int MaxN = 15*15+10+1000;
const int maxnode = MaxN * MaxM;
const int INF = 0x3f3f3f3f;
struct DLX
{
	int n,m,size;
	int U[maxnode],D[maxnode],R[maxnode],L[maxnode],Row[maxnode],Col[maxnode];
	int H[MaxN],S[MaxM];
	int ansd;
	void init(int _n,int _m)
	{
		n = _n;
		m = _m;
		for(int i = 0;i <= m;i++)
		{
			S[i] = 0;
			U[i] = D[i] = i;
			L[i] = i-1;
			R[i] = i+1;
		}
		R[m] = 0; L[0] = m;
		size = m;
		for(int i = 1;i <= n;i++)H[i] = -1;
	}
	void Link(int r,int c)
	{
	//	printf("%d %d\n",r,c);
		++S[Col[++size]=c];
		Row[size] = r;
		D[size] = D[c];
		U[D[c]] = size;
		U[size] = c;
		D[c] = size;
		if(H[r] < 0)H[r] = L[size] = R[size] = size;
		else
		{
			R[size] = R[H[r]];
			L[R[H[r]]] = size;
			L[size] = H[r];
			R[H[r]] = size;
		}
	}
	void remove(int c)
	{
		for(int i = D[c];i != c;i = D[i])
			L[R[i]] = L[i], R[L[i]] = R[i];
	}
	void resume(int c)
	{
		for(int i = U[c];i != c;i = U[i])
			L[R[i]] = R[L[i]] = i;
	}
	bool v[MaxM];
	int f()
	{
		int ret = 0;
		for(int c = R[0]; c != 0;c = R[c])v[c] = true;
		for(int c = R[0]; c != 0;c = R[c])
			if(v[c])
			{
				ret++;
				v[c] = false;
				for(int i = D[c];i != c;i = D[i])
					for(int j = R[i];j != i;j = R[j])
						v[Col[j]] = false;
			}
		return ret;
	}
	void Dance(int d)
	{
		if(d + f() >= ansd)return;
		if(R[0] == 0)
		{
			if(d < ansd)ansd = d;
			return;
		}
		int c = R[0];
		for(int i = R[0];i != 0;i = R[i])
			if(S[i] < S[c])
				c = i;
		for(int i = D[c];i != c;i = D[i])
		{
			remove(i);
			for(int j = R[i];j != i;j = R[j])remove(j);
			Dance(d+1);
			for(int j = L[i];j != i;j = L[j])resume(j);
			resume(i);
		}
	}
};
DLX g;
int a[MaxN];
int b[MaxM];
long long C[20][20];
void init2(){
	C[0][0] = 1;
	for(int i = 1;i < 20;i++){
		C[i][0] = C[i][i] = 1;
		for(int j = 1;j < i;j++)
			C[i][j] = C[i-1][j] + C[i-1][j-1];
	}
}
int main()
{
    //freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    init2();
    int T;
	int n,m,r;
	int iCase = 0;
	scanf("%d",&T);
	//while(T--){
  
    for(n = 0;n < 9;n++)
		for(m = 0;m < 9;m++)
			for(r = 0;r < 9;r++){
				if(n == 0 || m == 0 || r == 0){
					printf("0,");
					continue;
				}
				if( !(r <= m && m <= n) ){
					printf("0,");
					continue;
				}
		iCase++;
	//	scanf("%d%d%d",&n,&m,&r);
		if(n == 8 && m == 5 && r == 4){
			printf("0,");
			continue;
		}
		int cnt1 = 0;
		int cnt2 = 0;
		for(int i = 0;i < (1<<n);i++){
			int cc = 0;
			for(int j = 0;j < n;j++)
				if(i&(1<<j))
					cc++;
			if(cc == m)a[++cnt1] = i;
			if(cc == r)b[++cnt2] = i;
		}
		g.init(cnt1,cnt2);
		for(int i = 1;i <= cnt1;i++)
			for(int j = 1;j <= cnt2;j++)
				if((a[i]|b[j]) == a[i])
					g.Link(i,j);
		long long tmp = C[n][r];
		long long tmp2 = C[m][r];
		g.ansd = tmp;
		g.Dance(0);
		printf("%d,",g.ansd);
		//printf("Case #%d: %d\n",iCase,g.ansd);
			}
//	}
    return 0;
}