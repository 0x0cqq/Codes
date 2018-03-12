// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 1100;

bool edge[MAXN][MAXN];

int in[MAXN];
int topo[MAXN],ans[MAXN],cnt = 0,instack[MAXN];

int n,m,t,tmp[MAXN];

inline void init(){
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=m;i++){
        scanf("%d",&t);
        for(int i = 1;i<=t;i++)
            scanf("%d",&tmp[i]);
        int j = 1;
        for(int i = tmp[1];i<=tmp[t];i++){
            if(i!=tmp[j]){
                for(int j = 1;j<=t;j++)
                    edge[i][tmp[j]] = 1;
            }
            else
                ++j;
        }
    }
}

inline void solve(){
    queue<int> q;
    for(int i = 1;i<=n;i++)
        for(int j = 1;j<=n;j++)
            in[j]+=edge[i][j];
    for(int i = 1;i<=n;i++)
        if(in[i] == 0) q.push(i);
    while(!q.empty()){
        int nown = q.front();q.pop();
        topo[++cnt] = nown;
        for(int to = 1;to<=n;to++){
            if(edge[nown][to] && --in[to]==0)
                    q.push(to);
        }
    }
    int res = 0;
    for(int w = n;w>=1;w--){
        int i = topo[w];
        ans[i] = 1;
        for(int to = 1;to<=n;to++){
            if(edge[i][to])
                ans[i] = max(ans[i],ans[to]+1);
        }
        res = max(res,ans[i]);
    }
    printf("%d\n",res);
}

int main(){
    init();
    solve();
    return 0;
}