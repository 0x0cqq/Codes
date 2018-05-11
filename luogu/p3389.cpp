#include <cstdio>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;

const int MAXN = 400000;

vector<int> edge[MAXN];
 
void addedge(int a,int b){
    edge[a].push_back(b);
    edge[b].push_back(a);
}

struct q{
    int id,p,k;
    bool operator <(q w)const{
        return k < w.k;
    }
};

vector<q> qq[MAXN];

int n,m;
int siz[MAXN],dep[MAXN];
ll sum[MAXN],ans[MAXN];
int lowbit(int x){return x & (-x);}
ll query(int x){
    ll ans = 0;
    while(x) ans += sum[x],x -= lowbit(x);
    return ans;
}
void update(int x,ll d){
    while(x<=n) sum[x] += d,x += lowbit(x);
}

void init(){
    scanf("%d %d",&n,&m);
    int a,b;
    for(int i = 1;i<=n-1;i++){
        scanf("%d %d",&a,&b);
        addedge(a,b);
    }
    for(int i = 1;i<=m;i++){
        scanf("%d %d",&a,&b);
        qq[a].push_back((q){i,a,b});
    }
}

void dfs1(int x,int fa,int depth){
    siz[x] = 1;dep[x] = depth;
    for(int i = 0;i < edge[x].size();i++){
        int v = edge[x][i];
        if(v == fa) continue;
        dfs1(v,x,depth+1);
        siz[x] += siz[v];
    }   
}

void dfs2(int x,int fa){
    for(int i = 0;i < qq[x].size();i++){
        ans[qq[x][i].id] -= (1ll * query(min(qq[x][i].k + dep[x],n)) - 1ll * query(dep[x]));
    }
    for(int i = 0;i < edge[x].size();i++){
        int v = edge[x][i];
        if(v == fa) continue;
        dfs2(v,x);
    } 
    for(int i = 0;i < qq[x].size();i++){
        ans[qq[x][i].id] += (1ll * query(min(qq[x][i].k + dep[x],n)) - 1ll * query(dep[x])) + 1ll * min(dep[x]-1,qq[x][i].k)*(siz[x]-1);
    }
    update(dep[x],siz[x]-1);
}

void solve(){
    dfs1(1,0,1);
    dfs2(1,0);
    for(int i = 1;i<=m;i++){
        printf("%lld\n",ans[i]);
    }
}

int main(){
    init();
    solve();
    return 0;
}