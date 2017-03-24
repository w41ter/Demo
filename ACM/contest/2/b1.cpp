#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cctype>
using namespace std;
const int base[9]={1,1,2,6,24,120,720,5040,40320};
const int dx[4]={1,0,0,-1};//转移方向,遵从字典序最小
const int dy[4]={0,-1,1,0};
const int maxh=362880;//每种开始状态所对应状态数
int des;//用于存储目标状态hash值,判断是否不需要转移
struct pnt{
        int maz[3][3];
        int ind;//标记起始状态的编号
        int x,y;
        int hashCode;
        pnt(){
                x=y=hashCode=-1;
        }
        pnt(char * str){
                for(int i=0;i<9;i++){
                        if(str[i]=='X'){
                                maz[i/3][i%3]=9;
                                x=i/3;
                                y=i%3;
                                ind=i;
                        }
                        else maz[i/3][i%3]=str[i]-'0';
                }
        }
        int gethashcode(){
                int ans=0;
                for(int i=0;i<9;i++){
                        int cnt=0;
                        for(int j=0;j<i;j++){
                                if(maz[j/3][j%3]>maz[i/3][i%3]){
                                        cnt++;
                                }
                        }
                        ans+=base[i]*cnt;
                }
                return hashCode=ind*maxh+ans;
        }
};
bool in(int tx,int ty){
        return tx>=0&&tx<3&&ty>=0&&ty<3;
}

int vis[maxh*10+1];//用于存储某状态是否已被遍历,并存储由何种操作得到该状态
int pre[maxh*10+1];//用于存储某状态由何种状态转移得到
queue<pnt> que;
char ans[maxh*10+1];//存储答案的逆序
char buff[300];//存储输入
pnt s,e;
int ind[10],indlen;//用于重新编码
bool input(){
        if(scanf("%s",buff)!=1)return false;
        indlen=0;//重新编码
        for(int i=0;i<9;i++){
                if(buff[i]>='0'&&buff[i]<='9'){
                        s.maz[i/3][i%3]=++indlen;
                        ind[buff[i]-'0']=indlen;
                }
                else{
                        s.maz[i/3][i%3]=9;
                        s.x=i/3;
                        s.y=i%3;
                        s.ind=i;
                }
        }
        if(scanf("%s",buff)!=1)return false;
        for(int i=0;i<9;i++){
                if(buff[i]>='0'&&buff[i]<='9'){
                        e.maz[i/3][i%3]=ind[buff[i]-'0'];
                }
                else{
                        e.maz[i/3][i%3]=9;
                        e.x=i/3;
                        e.y=i%3;
                }
        }
        e.ind=s.ind;//起始状态相同
        des=e.gethashcode();
        return true;
}
void bfs(){
        while(!que.empty()){
                pnt tp=que.front();que.pop();
                int x=tp.x,y=tp.y;
                for(int i=0;i<4;i++){
                        int tx=x+dx[i],ty=y+dy[i];
                        if(in(tx,ty)){
                                pnt nw=tp;
                                swap(nw.maz[tx][ty],nw.maz[x][y]);
                                nw.x=tx,nw.y=ty;
                                if(vis[nw.gethashcode()]==-1){
                                        vis[nw.hashCode]=i;
                                        pre[nw.hashCode]=tp.gethashcode();
                                        que.push(nw);
                                }
                        }
                }
        }
}
void init(){
        memset(vis,-1,sizeof(vis));
        memset(pre,-1,sizeof(pre));
        pnt s1=pnt("12345678X");//9种起始状态加入序列
        vis[s1.gethashcode()]=-2;
        que.push(s1);
        pnt s2=pnt("1234567X8");
        vis[s2.gethashcode()]=-2;
        que.push(s2);
        pnt s3=pnt("123456X78");
        vis[s3.gethashcode()]=-2;
        que.push(s3);
        pnt s4=pnt("12345X678");
        vis[s4.gethashcode()]=-2;
        que.push(s4);
        pnt s5=pnt("1234X5678");
        vis[s5.gethashcode()]=-2;
        que.push(s5);
        pnt s6=pnt("123X45678");
        vis[s6.gethashcode()]=-2;
        que.push(s6);
        pnt s7=pnt("12X345678");
        vis[s7.gethashcode()]=-2;
        que.push(s7);
        pnt s8=pnt("1X2345678");
        vis[s8.gethashcode()]=-2;
        que.push(s8);
        pnt s9=pnt("X12345678");
        vis[s9.gethashcode()]=-2;
        que.push(s9);
        bfs();
}
int heap[maxh],sz;
int getans(pnt e){//逆序遍历
        sz=0;
        int last=e.gethashcode();
        while(pre[last]>=0){
                heap[sz++]=vis[last];
                last=pre[last];
        }
        return sz;
}
void print(){
        for(int i=sz-1;i>=0;i--){
                switch(heap[i]){
                case 0:
                        putchar('d');break;
                case 1:
                        putchar('l');break;
                case 2:
                        putchar('r');break;
                case 3:
                        putchar('u');break;
                }
        }
        putchar('\n');
}
int main(){
        int T;
        scanf("%d",&T);
        init();
        for(int ti=1;ti<=T;ti++){
                input();
                s.hashCode=s.gethashcode();
                if(s.hashCode==des){
                        printf("Case %d: 0\n",ti);
                        puts("");
                        continue;
                }
                vis[s.hashCode]=-2;
                int step=getans(e);
                printf("Case %d: %d\n",ti,step);
                print();
        }
        return 0;
}