#include<iostream>  
#include<cstring>  
#include<cstdio>  
#include<algorithm>  
#include<vector>  
#include<string>  
#include<set>  
#include<queue>  
#include<stack>  
#include<map>  
#include<cmath>  
#include<cstdlib>  
#define ll long long  
#define maxn 600010  
#define inf 1000000000  
#define linf (1LL<<50)  
using namespace std;  
inline ll read()  
{  
    ll x=0,f=1;char ch=getchar();  
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}  
    while(ch>='0'&&ch<='9'){x*=10;x+=ch-'0';ch=getchar();}  
    return x*f;  
}  
inline void read(char *s,int &ts)  
{  
    char x=getchar();  
    while(!(x>='a'&&x<='z'))x=getchar();  
    while(x>='a'&&x<='z')s[++ts]=x,x=getchar();  
}  
int n,m,que,tot=0;  
int q[maxn];  
struct data{  
    int to,next;  
}e[2*maxn];  
int head[maxn];  
int path[maxn];  
int d[maxn];  
int flag[maxn];  
int f[maxn];  
void line(int a,int b)  
{  
    tot++;  
    e[tot].to=b;  
    e[tot].next=head[a];  
    head[a]=tot;  
}  
int get(int x)  
{   
    return(x==f[x])?x:f[x]=get(f[x]);  
}  
int find(int x)  
{  
    d[x]=0;  
    flag[x]=x;  
    q[q[0]=1]=x;  
    int yuan=x;  
    for(int i=1;i<=q[0];i++)  
    {  
        int y=q[i];  
        for(int u=head[y];u;u=e[u].next)  
        if(flag[e[u].to]!=x)  
        {  
            flag[e[u].to]=x;  
            q[++q[0]]=e[u].to;  
            d[e[u].to]=d[y]+1;  
            if(d[e[u].to]>d[yuan])   
            yuan=e[u].to;  
        }  
    }  
    int y2=yuan;  
    d[yuan]=0;  
    q[q[0]=1]=yuan;  
    flag[yuan]=yuan;  
    for(int i=1;i<=q[0];i++)  
    {  
        int y=q[i];  
        for(int u=head[y];u;u=e[u].next)  
        if(flag[e[u].to]!=yuan)  
        {  
            flag[e[u].to]=yuan;  
            q[++q[0]]=e[u].to;  
            d[e[u].to]=d[y]+1;  
            if(d[e[u].to]>d[y2])  
            y2=e[u].to;  
        }  
    }  
    return d[y2];  
}  
int main()  
{  
    scanf("%d%d%d",&n,&m,&que);  
    for(int i=1;i<=n;i++)  
    f[i]=i;  
    for(int i=1;i<=m;i++)  
    {  
        int x,y;  
        scanf("%d%d",&x,&y);  
        line(x,y);  
        line(y,x);  
        if(get(x)!=get(y))  
        f[get(x)]=get(y);  
    }  
    for(int i=1;i<=n;i++)  
    if(i==get(i)) path[i]=find(i);  
    for(int i=1;i<=que;i++)  
    {  
        int pos;  
        scanf("%d",&pos);  
        if(pos==1)  
        {  
            int x;  
            scanf("%d",&x);  
            printf("%d\n",path[get(x)]);  
        }  
        else  
        {  
            int x,y;  
            scanf("%d%d",&x,&y);  
            x=get(x);y=get(y);  
            if(x==y) continue;  
            int u1=path[x];  
            int u2=path[y];  
            f[x]=y;  
            path[y]=(u1+1)/2+(u2+1)/2+1;  
            if(path[y]<u1) path[y]=u1;  
            if(path[y]<u2) path[y]=u2;  
        }  
    }  
    return 0;  
}