#include <cstdio>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;
 
namespace normal_io{
    inline char read(){return getchar();}
    inline void read(int &x){scanf("%d",&x);}
    inline void read(char *x){scanf("%s",x);}
    inline void print(int x){printf("%d",x);}
    inline void print(char x){putchar(x);}
    inline void flush(){return;}
}using namespace normal_io;

const int MAXN = 110000;

int n,col[MAXN];

//-----
vector<int> edge[MAXN];
int f[MAXN],vis[MAXN],siz[MAXN];
int rt,sz;

//-----
ll ans[MAXN],tmp[MAXN],tot;
int c[MAXN];

void getroot(int nown,int fa){
    f[nown] = 0,siz[nown] = 1;
    for(int i = 0;i<edge[nown].size();i++){
        int v = edge[nown][i];
        if(vis[v] || v == fa) continue;
        getroot(v,nown);
        siz[nown] += siz[v];
        f[nown] = max(f[nown],siz[v]);
    }
    f[nown] = max(f[nown],sz - siz[nown]);
    if(f[nown] < f[rt]) rt = nown;
}

void dfs1(int nown,int fa,int d){
    if((c[col[nown]]++) == 0)
        tmp[col[nown]] += d*siz[nown],tot+=d*siz[nown];
    for(int i = 0;i<edge[nown].size();i++){
        int v = edge[nown][i];
        if(vis[v] || v == fa) continue;
        dfs1(v,nown,d);
    }
    --c[col[nown]];
}

void getsize(int nown,int fa){
    siz[nown] = 1;
    for(int i = 0;i < edge[nown].size();i++){
        int v = edge[nown][i];
        if(vis[v] || v == fa) continue;
        getsize(v,nown);
        siz[nown] += siz[v];
    }
}

void cal(int nown,int fa,int wh){
    ll t = tmp[col[nown]];
    tot += sz - siz[wh] - tmp[col[nown]];
    tmp[col[nown]] = sz - siz[wh];
    ans[nown] += tot;
    //printf("add:%d %d\n",nown,int(tot));
    for(int i = 0;i < edge[nown].size();i++){
        int v = edge[nown][i];
        if(v == fa || vis[v]) continue;
        cal(v,nown,wh);
    }
    tmp[col[nown]] = t;
    tot -= sz - siz[wh] - tmp[col[nown]];
}

void work(int nown){
    tot = 0;
    getsize(nown,0);
    sz = siz[nown];
    dfs1(nown,0,1);
    /*printf("%d\n",nown);
    for(int i = 1;i <= n;i++){
        printf("%d ",int(tmp[i]));
    }
    printf("\n");*/
    ans[nown] += tot;
    //printf("add:%d %d\n",nown,int(tot));
    for(int i = 0;i < edge[nown].size();i++){
        int v = edge[nown][i];
        if(vis[v]) continue;
        dfs1(v,nown,-1);
        tot += sz - siz[v] - tmp[col[nown]];
        tmp[col[nown]] = sz - siz[v]; 
        /*printf("v:%d %lld\n",v,tot);
        for(int i = 1;i <= n;i++){
            printf("%d ",int(tmp[i]));
        }
        printf("\n");*/
        cal(v,nown,v);
        dfs1(v,nown,1);
        tot += siz[nown] - tmp[col[nown]];
        tmp[col[nown]] = siz[nown];
    }
    dfs1(nown,0,-1);
    //
}

void solve(int nown){
    vis[nown] = 1;
    work(nown);
    for(int i = 0;i < edge[nown].size();i++){
        int v = edge[nown][i];
        if(vis[v]) continue;
        f[rt = 0] = sz = siz[v];
        getroot(v,rt);
        solve(rt);
    }
}

void init(){
    read(n);
    int a,b;
    for(int i = 1;i <= n;i++){
        read(col[i]);
    }
    for(int i = 1;i<=n-1;i++){
        read(a),read(b);
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
}

void solve(){
    f[rt = 0] = sz = n;
    getroot(1,rt);
    solve(rt);
    for(int i = 1;i <= n;i++){
        printf("%lld\n",ans[i]);
    }
}

int main(){
    //freopen("in.txt","r",stdin);
    //freopen("1.out","w",stdout);
    init();
    solve();
    return 0;
}