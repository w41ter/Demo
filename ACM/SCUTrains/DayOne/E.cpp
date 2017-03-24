#include<stdlib.h>
#include<stdio.h>
int maxx,minn,lin[100005],n;

int main(){
	
    int i,k,p,o,m;
    scanf("%d",&n);
	
    for(i=0;i<n;i++){
        scanf("%d",&lin[i]);
    }
	
    minn=lin[0];
    maxx=lin[n-1];
    printf("%d %d\n",lin[1]-lin[0],lin[n-1]-lin[0]);
	
    for(i=1;i<n-1;i++){
		
        k=lin[i]-lin[i-1];
        p=lin[i+1]-lin[i];
        if(k>p) k=p;
        printf("%d ",k);
        k=maxx-lin[i];
        p=lin[i]-minn;
        if(k<p) k=p;
        printf("%d\n",k);
    }
    printf("%d %d\n",lin[n-1]-lin[n-2],lin[n-1]-lin[0]);
    return 0;
}
