#include <iostream>  
#include <queue>  
#include <string.h>  
#include <cstdio>
using namespace std;  
int maxData = 0x7fffffff; 
queue<int> dl;
int head[5001],cost[100001],net[100001],to[100001],cap[100001];
int cnt=1;
int tot=0; 
void add(int x,int y,int c,int z)
{
    to[++cnt]=y;
    cost[cnt]=z;
    cap[cnt]=c;
    net[cnt]=head[x];
    head[x]=cnt;
}
int flow[5001];
int pre[5001];
int xb[5001];
int mflow=0;
int mcost=0;
int dis[5001];
int f[5001];
int n,m;
void make_map(int from,int ds,int cost1)
{
    if(from==1)//当起点为1时，从起点到终点的入点连一条边
    {
        add(1,ds,1,cost1);
        add(ds,1,0,-cost1);
        return;
    }
    if(ds==n)//当终点为n时，从起点的出点到n连一条边
    {
        add(from+n,n,1,cost1);
        add(n,from+n,0,-cost1);
        return;
    }
    add(from+n,ds,1,cost1);//起点不是1，终点不是n，从起点的出点到终点的入点连一条边
    add(ds,from+n,0,-cost1);
    return;
}
int BFS(int s,int t)
{
    memset(dis,127,sizeof(dis));
    memset(f,0,sizeof(f));
    int INF=dis[0];
    while(!dl.empty())
     dl.pop();
    for(int i=1;i<=n;i++)
     pre[i]=-1;
    f[s]=1;
    dis[s]=0;
    pre[s]=0;
    flow[s]=maxData;
    dl.push(s);
    while(!dl.empty())
    {
        int dd=dl.front();
        dl.pop();
        f[dd]=0;
        for(int i=head[dd];i;i=net[i])
        {
            int tmp=to[i];
            if(cap[i]>0&&dis[tmp]>dis[dd]+cost[i])
           {
              dis[tmp]=dis[dd]+cost[i];
              pre[tmp]=dd;
              xb[tmp]=i;
              flow[tmp]=min(flow[dd],cap[i]);
              if(!f[tmp]) f[tmp]=1,dl.push(tmp);
           }
        }
    }
    if(dis[t]>=INF) return 0;
    return 1;
}
void max_flow(int s,int t)
{
    while(BFS(s,t))
    {
        int k=t;
        while(k!=s)
         {
             cap[xb[k]]-=flow[t];
             cap[xb[k]^1]+=flow[t];
             k=pre[k];
         } 
        mflow+=flow[t];
        mcost+=flow[t]*dis[t];
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=2;i<n;i++)
     add(i,i+n,1,0),add(i+n,i,0,0);//预处理出入点与出点之间的路，模拟路径不能交叉的过程
    for(int i=1;i<=m;i++)
     {
         int x,y,c,d;
         scanf("%d%d%d",&x,&y,&d);
         make_map(x,y,d); //添加边
     }
    max_flow(1,n);
    printf("%d %d",mflow,mcost);//输出
    return 0;
}