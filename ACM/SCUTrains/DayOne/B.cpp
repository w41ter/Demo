#include<stdlib.h>
#include<stdio.h>
char pan[30];
int pasen[1000005],noww=0,maxx=0,n,zong[105][2];
int main(){
    int i,k,o,p,j;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%s",pan);
        scanf("%d",&p);
        if(pan[0]=='+'){
            zong[i][0]=1;
            zong[i][1]=p;
            pasen[p]=1;
        }
        if(pan[0]=='-'){
            zong[i][0]=2;
            zong[i][1]=p;
            if(pasen[p]==0){
                maxx++;
            }
            if(pasen[p]==1){
                pasen[p]--;
            }
        }
    }
    noww=maxx;
    for(i=0;i<n;i++){
        if(zong[i][0]==1){
            noww++;
            if(noww>maxx) maxx=noww;
        }
        if(zong[i][0]==2){
            noww--;
        }
    }
    printf("%d\n",maxx);
    return 0;
}
