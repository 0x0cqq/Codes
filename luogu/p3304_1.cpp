#include<stdio.h>
#define maxn 233333
int father[maxn],head[maxn],n,tot,l,r,p;
long long maxd,dep[maxn];//最长与深度
bool isofd[maxn],flag;//对第一条直径（标准直径）的点标记 
struct hhh{int to,w,next;}edge[2*maxn];//邻接表
void add(int x,int y,int z)//加边
{
    edge[++tot].to=y;      edge[tot].w=z;
    edge[tot].next=head[x];    head[x]=tot;
}
void dfs1(int u,int fa)//算直径的深搜 
{
    father[u]=fa;//记爸爸 
    for(int i=head[u];i;i=edge[i].next)
    {
        int v=edge[i].to;if(v==fa)    continue;//只能遍历儿子 
        dep[v]=dep[u]+edge[i].w;
        if(dep[v]>maxd)    p=v,maxd=dep[v];//最远（深）的点和距离 
        dfs1(v,u);
    }
}
void dfs2(int u,int fa)//搜索标准直径上每一个点的子树深度 
{
    for(int i=head[u];i;i=edge[i].next)
    {
        int v=edge[i].to;if(v==fa||isofd[v])    continue;
        dep[v]=dep[u]+edge[i].w;//dep没用了，随便改 
        if(dep[v]>maxd)    maxd=dep[v];//最深 
        dfs2(v,u);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        add(a,b,c);        add(b,a,c);
    }
    dfs1(1,0);    l=p;//以任意一个点为根搜最深作为标准直径左端点 
    dep[p]=maxd=0;    dfs1(l,0);    r=p;//以左端点为根搜最深即为又端点 
    printf("%lld\n",maxd);
    //喜：直径结束！！QAQ
    for(int i=r;i;i=father[i])    isofd[i]=true;//标记标准诗经上的点
    int ll=l,rr=r;                    //避免搜索的深度与标准直径重复 
    for(int i=father[rr];i!=ll;i=father[i])
    {
        int ld=dep[i],rd=dep[rr]-dep[i];//该点到左右端点的距离 
        dep[i]=maxd=0;//dep过去就没用了，清空状态，搜索子树深度 
        dfs2(i,0);
        if(maxd==rd)    r=i;
        //如果子树深度与到右端点的距离相同，那么意味着从这点还有其他直径分出，缩短树干右端点 
        if(maxd==ld&&!flag)    flag=true,l=i;//因为从右遍历，左端点剪一次为最佳 
    }
    maxd=1;//改记缩短后的r~l经过边数
    for(int i=father[r];i!=l;i=father[i])    maxd++;
    printf("%d\n",maxd);
    return 0; 
}