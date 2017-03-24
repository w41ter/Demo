#include<iostream>
#include<queue>
using namespace std;
 
#define N 10
#define MAX 365000
 
char visited[MAX];
int father1[MAX];  // 保存正向搜索当前状态的父亲状态结点
int father2[MAX];  // 保存反向搜索当前状态的父亲状态结点
int move1[MAX];    // 正向搜索的方向保存
int move2[MAX];   //  反向搜索的方向保存
 
struct Status   // 结构
{
       char eight[N];  // 八数码状态
       int space;     // x 位置
       int state;    // hash值,用于状态保存与判重 
};
 
queue<Status> Q1;  // 正向队列
queue<Status> Q2;  // 反向队列
 
Status s,s1,s2,t;
 
bool found;  // 搜索成功标记
 
int state;   // 正反搜索的相交状态
 
int factory[]={1,1,2,6,24,120,720,5040,40320,362880};  // 0..n的阶乘
 
int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
 
int Gethash(char eight[])  // 康托展开(获取状态，用于判重)
{
       int k=0;
       for(int i=0;i<9;i++)
       {
              int t=0;
              for(int j=i+1;j<9;j++)
                     if(eight[j]<eight[i])
                            t++;
              k+=(t*factory[9-i-1]);
       }
       return k;
}
 
int ReverseOrder(char eight[])  // 求状态的逆序数
{
       int i,j,num=0;
       for(i=0;i<9;i++)
       {
              for(j=0;j<i;j++)
              {
                     if(int(eight[i])==9)
                     {
                            break;
                     }
                     if(int(eight[j])==9)
                            continue;
                     if(int(eight[j])>int(eight[i]))
                            num++;
              }
       }
       num=num%2;
       return num;
}
 
void BFS_expand(queue<Status> &Q,bool flag)  // 单向广度搜索
{
       int k,x,y;
       s=Q.front();
       Q.pop();
       k=s.space;
       x=k/3;
       y=k%3;
       for(int i=0;i<4;i++)
       {
              int xx=x+dir[i][0];
              int yy=y+dir[i][1];
              if(xx>=0 && xx<=2 && yy>=0 && yy<=2)
              {
                     t=s;
                     t.space=xx*3+yy;   // 计算x位置
                     swap(t.eight[k],t.eight[t.space]);  // 交换两个数位置
                     t.state=Gethash(t.eight);
                     if(flag)  // 在正向队列中判断
                     {
                            if(visited[t.state]!=1 && ReverseOrder(t.eight)==0)  // 未在正向队列出现过并且满足奇偶性
                            {
                                   move1[t.state]=i;  // 保存正向搜索的方向
                                   father1[t.state]=s.state; // 保存正向搜索当前状态的父亲状态结点
                                   if(visited[t.state]==2)   //  当前状态在反向队列中出现过
                                   {
                                          state=t.state;  // 保存正反搜索中相撞的状态(及相交点)
                                          found=true;    // 搜索成功
                                          return;
                                   }
                                   visited[t.state]=1;   // 标记为在正向队列中
                                   Q.push(t);  // 入队
                            }
                     }
                     else  // 在反向队列中判断
                     {
                            if(visited[t.state]!=2 && ReverseOrder(t.eight)==0)   // 未在反向队列出现过并且满足奇偶性
                            {
                                   move2[t.state]=i;  // 保存反向搜索的方向
                                   father2[t.state]=s.state; // 保存反向搜索当前状态的父亲状态结点
                                   if(visited[t.state]==1)  //  当前状态在正向队列中出现过
                                   {
                                          state=t.state;  // 保存正反搜索中相撞的状态(及相交点)
                                          found=true;   // 搜索成功
                                          return;
                                   }
                                   visited[t.state]=2;  // 标记为在反向队列中
                                   Q.push(t);   // 入队
                            }
                     }
              }
       }
       return ;
}
 
void TBFS()            // 双向搜索
{
       memset(visited,0,sizeof(visited));
       while(!Q1.empty())
              Q1.pop();
       while(!Q2.empty())
              Q2.pop();
       visited[s1.state]=1;   // 初始状态
       father1[s1.state]=-1;
       visited[s2.state]=2;   // 目标状态
       father2[s2.state]=-1;
       Q1.push(s1);
       Q2.push(s2);
       while(!Q1.empty() || !Q2.empty())
       {
              if(!Q1.empty())
                     BFS_expand(Q1,true);
              if(found)
                     return ;
              if(!Q2.empty())
                     BFS_expand(Q2,false);
              if(found)
                     return ;
       }
}
 
void PrintPath1(int father[],int move[])   // 从相交状态向初始状态寻找路径
{
       int n,u;
       char path[1000];
       n=1;
       path[0]=move[state];
       u=father[state];
       while(father[u]!=-1)
       {
              path[n]=move[u];
              n++;
              u=father[u];
       }
       for(int i=n-1;i>=0;--i)
       {       
              if(path[i] == 0)           
                     printf("u");       
              else if(path[i] == 1)           
                     printf("d");       
              else if(path[i] == 2)           
                     printf("l");       
              else           
                     printf("r");   
       }
}
 
void PrintPath2(int father[],int move[])   // 从相交状态向目标状态寻找路径
{
       int n,u;
       char path[1000];
       n=1;
       path[0]=move[state];
       u=father[state];
       while(father[u]!=-1)
       {
              path[n]=move[u];
              n++;
              u=father[u];
       }
       for(int i=0;i<=n-1;i++)
       {       
              if(path[i] == 0)           
                     printf("d");       
              else if(path[i] == 1)           
                     printf("u");       
              else if(path[i] == 2)           
                     printf("r");       
              else           
                     printf("l");   
       }
}
 
int main()
{
       int i;
       char c;   
       while(scanf(" %c",&c)!=EOF)
       {
              if(c=='x')
              {
                     s1.eight[0]=9;
                     s1.space=0;
              }
              else
                     s1.eight[0]=c-'0';
              for(i=1;i<9;i++)
              {
                     scanf(" %c",&c);
                     if(c=='x')
                     {
                            s1.eight[i]=9;
                            s1.space=i;
                     }
                     else
                            s1.eight[i]=c-'0';
              }
              s1.state=Gethash(s1.eight);
              for(int i=0;i<9;i++)
                     s2.eight[i]=i+1;
              s2.space=8;
              s2.state=Gethash(s2.eight);
              if(ReverseOrder(s1.eight)==1)
              {
                     cout<<"unsolvable"<<endl;
                     continue;
              }
              found=false;
              TBFS();
              if(found)   // 搜索成功
              {
                     PrintPath1(father1,move1);
                     PrintPath2(father2,move2);
              }
              else
                     cout<<"unsolvable"<<endl;
              cout<<endl;
       }
       return 0;
}