#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

inline int max(int a, int b){
    return a>b ? a : b;
}

typedef struct{
    int v;
    int next;
}edge_t;

int head[101];
edge_t edges[100];
int f[101][101];
int v[101];
int M,N;

void dfs(int i){
    f[i][0]=0;
    f[i][1]=v[i];
	cout << "dfs : " <<  i << endl;
    for(int p=head[i]; p!=0; p=edges[p].next){
        dfs(edges[p].v);
        for(int m=M; m>=2; m--){
            for(int k=1; k<=m-1; k++){
                f[i][m]=max(f[i][m], f[i][k]+f[edges[p].v][m-k]);
            }
        }
    }
	cout << "now dp[t][m] = " << f[i][M] << endl;
	cout << "end dfs :" << endl;
}

int main(){
	freopen("1.txt", "rb+", stdin);
    memset(edges, 0, sizeof(edges));
    memset(head, 0, sizeof(head));
    memset(f, 0, sizeof(f));
    scanf("%d%d", &N, &M);
    for(int i=1; i<=N; i++){
        scanf("%d", v+i);
    }
    int u,v;
    for(int i=1; i<=N-1; i++){
        scanf("%d%d", &u, &v);
        edges[i].v=v;
        edges[i].next = head[u];
        head[u]=i;
    }

    dfs(1);
    printf("%d", f[1][M]);
    return 0;
}
