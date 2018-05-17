#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

namespace normal_io{
    inline char read(){return getchar();}
    inline void read(int &x){scanf("%d",&x);}
    inline void read(char *x){scanf("%s",x);}
    inline void print(int x){printf("%d",x);}
    inline void print(char x){putchar(x);}
    inline void flush(){return;}
}using namespace normal_io;

const int MAXN = 310000;

int n,m,q;
vector<int> edge[MAXN];
int f[MAXN],r[MAXN];
int find(int x){
    return f[x]==x?x:find(f[x]);
}

void un(int x,int y){
    int fx = find(x),fy = find(y);
    //printf("x:%d %d y:%d %d",fx,r[fx],y,r[fy]);
    if(fx == fy) return;
    if(r[fx] < r[fy]) swap(fx,fy);
    if((r[fy]+1)/2 < r[fx]/2 && r[fx] != 0) 
        f[fy] = fx;
    else{
        r[fx] = (r[fx]+1)/2 + (r[fy]+1)/2 + 1;
        f[fy] = fx;
    }
    //printf(" %d\n",r[fx]);
}

void init(){
    read(n),read(m),read(q);
    int a,b;
    for(int i = 1;i<=n;i++){
        f[i] = i;
    }
    for(int i = 1;i<=m;i++){
        read(a),read(b);
        edge[a].push_back(b);
        edge[b].push_back(a);
        f[find(b)] = find(a);
    }
}

int dis[MAXN];

int dfs1(int nown,int fa){
    int ans = nown;
    for(int i = 0;i<edge[nown].size();i++){
        int v = edge[nown][i];
        if(v == fa) continue;
        dis[v] = dis[nown]+1;
        int t = dfs1(v,nown);
        if(dis[t] > dis[ans]) ans = t;
    }
    return ans;
}

int dfs2(int nown,int fa){
    int ans = dis[nown];
    for(int i = 0;i<edge[nown].size();i++){
        int v = edge[nown][i];
        if(v == fa) continue;
        dis[v] = dis[nown] + 1;
        ans = max(ans,dfs2(v,nown));
    }
    return ans;
}

int getr(int i){
    dis[i] = 0;
    int u = dfs1(i,0);
    dis[u] = 0; 
    int ans = dfs2(u,0);
    //printf("%d %d %d\n",i,u,ans);
    return ans;
}

void build(){
    //memset(dis,0,sizeof(dis));
    for(int i = 1;i<=n;i++){
        if(r[find(i)] == 0)
            r[find(i)] = getr(i);
    }
}

void solve(){
    int op,a,b;
    for(int i = 1;i<=q;i++){
        read(op),read(a);
        if(op == 1){
            print(r[find(a)]),print('\n');
        }
        else if(op == 2){
            read(b);
            un(a,b);
        }
    }
}

int main(){
    init();
    build();
    solve();
    flush();
    return 0;
}