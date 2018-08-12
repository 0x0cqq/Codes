#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 110000;

vector<int> edge[MAXN];

int n,m,a,b,k;

int dis[MAXN];
queue<int> q;
void bfs(){
    memset(dis,0x3f,sizeof(dis));
    dis[k] = 0;
    q.push(k);
    while(!q.empty()){
        int nown = q.front(); q.pop();
        for(int i = 0;i<edge[nown].size();i++){
            int v = edge[nown][i];
            if(dis[v] > dis[nown] + 1){
                dis[v] = dis[nown] + 1;
                q.push(v);
            }
        }
    }
}

int cal(int d){
    return min(d*a,(d%2) * a + (d/2) * b);
}

void init(){
    scanf("%d %d %d %d %d",&n,&m,&k,&a,&b);
    int u,v;
    for(int i = 1;i<=m;i++){
        scanf("%d %d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
}

void solve(){
    bfs();
    for(int i = 1;i<=n;i++){
        printf("%d\n",cal(dis[i]));
    }
}

int main(){
    init();
    solve();
    return 0;
}