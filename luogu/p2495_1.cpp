#include<bits/stdc++.h>
using namespace std;

#define ch_top 20000000
char ch[ch_top],*now_r=ch;
void read(int &x)
{
    while (*now_r<48) ++now_r;
    for (x=*now_r-48;*++now_r>=48;)
     x=(x<<1)+(x<<3)+*now_r-48;
}

#define ll long long 
ll min(ll &x,ll &y) 
{
 return x<y?x:y;
}
void chmin(int &x,int y)
{
    if (x>y) x=y;
}
#define N 250100
int n,x,y,w;
int t[N];
struct edge
{
    int to,w,next;
}l[N<<1];int e;
void add_e(int x,int y,int w) 
{
  l[++e]={y,w,t[x]};t[x]=e;
}
void _add(int x,int y) 
{
 l[y].next=t[x];t[x]=y;
}

struct tree
{
    int f,deep,sz,top,c;
    int dfn,w;//dfs序；到根的min边权 
}T[N];

void dfs(int x,int deep,int f,int w)
{
    T[x].sz=1;T[x].deep=deep;T[x].f=f;T[x].w=w;
    ++deep;
    int i,y,c=0;
    for (i=t[x];i;i=l[i].next)
    if ((y=l[i].to)!=f)
    {
        dfs(y,deep,x,min(w,l[i].w));
        T[x].sz+=T[y].sz;
        if (T[y].sz>T[c].sz) c=y;
    }
    T[x].c=c;
}

int i,j,len;

int tot;
void dfs2(int x,int top)
{
    T[x].dfn=++tot;
    T[x].top=top;
    int c=T[x].c;
    if (!c) return;
    dfs2(c,top);

    int i,y;
    for (i=t[x];i;i=l[i].next)
    if ((y=l[i].to)!=T[x].f&&y!=c)
     dfs2(y,y);
}

int q[N],k;
bool dfn_xiao(int x,int y)
{
    return T[x].dfn<T[y].dfn;
}

int fx,fy;
int get_lca(int x,int y)
{
    fx=T[x].top;fy=T[y].top;
    while (fx!=fy)
    if (T[fx].deep>T[fy].deep) {x=T[fx].f;fx=T[x].top;}
    else {y=T[fy].f;fy=T[y].top;}
    return T[x].deep<T[y].deep?x:y;
}

int st[N],top,pre,lca;
int have[N],num;
void push(int now)
{
    pre=st[top];
    if (pre==1) {st[++top]=now;return;}

    lca=get_lca(now,pre);if (lca==pre) return ;//剪枝
    while (lca!=pre)
    {
        fx=st[--top];
        if (T[fx].dfn<T[lca].dfn) 
        {
         _add(lca,pre);
         st[++top]=lca;
         break;
        }
        _add(fx,pre);
        pre=fx; 
    }
    st[++top]=now;
} 

ll dp(int x)
{
    if (!t[x]) return T[x].w;

    ll ans=0;
    for (int i=t[x];i;i=l[i].next) 
     ans+=dp(i);
    t[x]=0;

    return min(ans,(ll)T[x].w);
}

int main()
{ freopen("1.in","r",stdin);freopen("1.out","w",stdout);
    fread(ch,1,ch_top,stdin);
    int n;
    read(n);
    for (i=1;i<n;++i)
    {
        read(x);read(y);read(w);
        add_e(x,y,w); add_e(y,x,w);
    }

    dfs(1,0,0,1<<30);
    dfs2(1,1);

    for (i=1;i<=n;++i) t[i]=0;
    int m;ll ans;
    read(m);
    while (m--)
    {
        read(k);
        for (i=1;i<=k;++i) read(q[i]);
        sort(q+1,q+k+1,dfn_xiao);

        st[top=1]=1;
        for (i=1;i<=k;++i) 
         push(q[i]);

        while (--top) _add(st[top],st[top+1]);

        ans=0;
        for (int i=t[1];i;i=l[i].next) 
          ans+=dp(i);
        t[1]=0;
        printf("%lld\n",ans);
    }
}