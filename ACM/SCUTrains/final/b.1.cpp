#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

const int VM=120;

struct Edge{
    int to,nxt;
    int cap;
}edge[VM<<1];

int n,T,cnt,head[VM];
int dp[VM][520],val[VM];    //dp[i][j]表示从第i个点开始，回到i点，花费j时间得到的最大财富值

void addedge(int cu,int cv,int cw){
    edge[cnt].to=cv;
    edge[cnt].cap=cw;
    edge[cnt].nxt=head[cu];
    head[cu]=cnt++;
}

int time1;

int DFS1(int u,int pre){    //找从1到N的最短时间
    if(u==n)
        return 1;
    for(int i=head[u];i!=-1;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==pre)
            continue;
        if(DFS1(v,u)){
            time1+=edge[i].cap;
            edge[i].cap=0;
            return 1;
        }
    }
    return 0;
}
/*

void spfa(int s){
    queue<int>que;
    int vis[N];
    mem(vis,0);mem(pre,0);
    for(int i=1;i<=n;i++)
        if(i==s)
            dist[i]=0;
        else
            dist[i]=inf;
    que.push(s);
    vis[s]=1;
    while(!que.empty()){
        int u=que.front();
        que.pop();
        vis[u]=0;
        for(int i=start[u];i!=-1;i=edge[i].next){
            int v=edge[i].v,w=edge[i].w;
            if(dist[v]>dist[u]+w){
                dist[v]=dist[u]+w;
                pre[v]=u;
                p[v]=i;
                if(!vis[v]){
                    vis[v]=1;
                    que.push(v);
                }
            }
        }
    }
    for(int i=n;i!=1;i=pre[i]){
        edge[p[i]].w=0;
        edge[p[i]^1].w=0;
    }
}

*/

void DFS2(int u,int pre){
    for(int i=0;i<=T;i++)
        dp[u][i]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==pre)
            continue;
        DFS2(v,u);
        int cost=edge[i].cap*2; //要走两遍
        for(int j=T;j>=cost;j--)
            for(int k=0;k<=j-cost;k++)
                dp[u][j]=max(dp[u][j],dp[v][k]+dp[u][j-cost-k]);
    }
}

int main(){

    //freopen("input.txt","r",stdin);

    while(~scanf("%d%d",&n,&T)){
        cnt=0;
        memset(head,-1,sizeof(head));
        int u,v,w;
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            addedge(u,v,w);
            addedge(v,u,w);
        }
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        time1=0;
        DFS1(1,-1);
        if(T<time1){
            printf("Human beings die in pursuit of wealth, and birds die in pursuit of food!\n");
            continue;
        }
        T-=time1;
        DFS2(1,-1);
        printf("%d\n",dp[1][T]);
    }
    return 0;
}