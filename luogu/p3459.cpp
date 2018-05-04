#include <cstdio>
#include <vector>
#include <cstdio>
using namespace std;

const int MAXN = 300000;

vector<int> edge[MAXN];

int n,m,cnt = 1,id[MAXN],pre[MAXN],dep[MAXN],siz[MAXN];

namespace BIT{
    int tree[MAXN];
    int lowbit(int x){
        return x & (-x);
    }
    void update(int pos,int d){
        while(pos <= n){
            tree[pos] += d;
            pos += lowbit(pos);
        }
    }
    int query(int pos){
        int ans = 0;
        while(pos >= 1){
            ans += tree[pos];
            pos -= lowbit(pos);
        }
        return ans;
    }
}

void dfs(int nown,int fa,int depth){
    pre[cnt] = nown;id[nown] = cnt++;dep[nown] = depth;
    siz[nown] = 1;
    for(int i = 0;i<edge[nown].size();i++){
        int v = edge[nown][i];
        if(v == fa) continue;
        dfs(v,nown,depth+1);
        siz[nown] += siz[v];
    }
}

void init(){
    scanf("%d",&n);
    int a,b;
    for(int i = 1;i<=n-1;i++){
        scanf("%d %d",&a,&b);
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
}

void solve(){
    dfs(1,0,0);
    for(int i = 1;i<=n;i++){
        BIT::update(i,dep[pre[i]] - dep[pre[i-1]]);
    }
    scanf("%d",&m);
    for(int i = 1;i<=m+n-1;i++){
        char op[20];int a,b;
        scanf("%s",op);
        if(op[0] == 'A'){
            scanf("%d %d",&a,&b);
            if(id[a] > id[b]) swap(a,b);
            BIT::update(id[b],-1),BIT::update(id[b] + siz[b],1);
        }
        else if(op[0] == 'W'){
            scanf("%d",&a);
            printf("%d\n",BIT::query(id[a]));
        }
        else if(op[0] == 'P'){
            for(int i = 1;i<=n;i++){
                printf("%d:%d(pre:%d tree:%d)\n",i,BIT::query(i),pre[i],BIT::tree[i]);
            }
            --i;           
        }
    }
}

int main(){
    init();
    solve();
    return 0;
}