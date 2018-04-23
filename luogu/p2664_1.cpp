#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1000;

int n;
int c[MAXN],t[MAXN],num = 0;

vector<int> edge[MAXN];

long long ans[MAXN];

void dfs(int nown,int fa,int start){
    if(t[c[nown]]++ == 0)
        num++;
    ans[nown] += num;
    for(int i = 0; i < edge[nown].size();i++){
        int v = edge[nown][i];
        if(v == fa) continue;
        dfs(v,nown,start);
    }
    if(--t[c[nown]] == 0)
        num--;
}

void init(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%d",&c[i]);
    }
    int a,b;
    for(int i = 1;i<=n-1;i++){
        scanf("%d %d",&a,&b);
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
}

void solve(){
    for(int i = 1;i<=n;i++){
        dfs(i,0,i);
    }
    for(int i = 1;i<=n;i++){
        printf("%lld\n",ans[i]);
    }
}

int main(){
    freopen("in.txt","r",stdin);
    freopen("2.out","w",stdout);
    init();
    solve();
    return 0;
}