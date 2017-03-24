#include <iostream>
using namespace std;
const int MAXN = 100000;
int wa[MAXN],wb[MAXN],wv[MAXN],WS[MAXN], r[MAXN], sa[MAXN];

void print(char *str, int *r, int n)
{
	cout << str << " is: \n";
	for (int i = 0; i < n; ++i)
		cout << r[i] << ' ';
	cout << endl;
}

int cmp(int *r,int a,int b,int l)
{return r[a]==r[b]&&r[a+l]==r[b+l];}

void da(int *r,int *sa, int n,int m)
{
	int i,j,p,*x=wa,*y=wb,*t; 
	for(i=0;i<m;i++) WS[i]=0; 
	for(i=0;i<n;i++) WS[x[i]=r[i]]++; 
	for(i=1;i<m;i++) WS[i]+=WS[i-1]; 
	for(i=n-1;i>=0;i--) sa[--WS[x[i]]]=i; 
	for(j=1,p=1;p<n;j*=2,m=p) 
	{ 
		print("sa", sa, n);
		for(p=0,i=n-j;i<n;i++) y[p++]=i; 
		print("y", y, n);
		for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j; 
		print("y", y, n);
		for(i=0;i<n;i++) wv[i]=x[y[i]]; 
		for(i=0;i<m;i++) WS[i]=0; 
		for(i=0;i<n;i++) WS[wv[i]]++; 
		for(i=1;i<m;i++) WS[i]+=WS[i-1]; 
		for(i=n-1;i>=0;i--) sa[--WS[wv[i]]]=y[i]; 
		for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++) 
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++; 
	} 
	return; 
}
 
int main() {
    int c, n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> c; 
		r[i] = c;
    }

	da(r, sa, n, 10);
	
    return 0;
}