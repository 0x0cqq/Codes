// luogu-judger-enable-o2
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 150;

int n,m;

vector<int> edge1[MAXN],edge2[MAXN];

void init(){
    scanf("%d %d",&n,&m);
    int a,b;
    for(int i = 1;i<=m;i++){
        scanf("%d %d",&a,&b);
        edge1[a].push_back(b),edge2[b].push_back(a);
    }
}

int bfs1(int s){
    bool vis[MAXN];
    queue<int> q;
    memset(vis,0,sizeof(vis));
    int ans = 0;
    if(!q.empty()) q.pop();
    q.push(s);
    while(!q.empty()){
        int nown = q.front();q.pop();
        if(vis[nown]) continue;
        ans++;vis[nown] = 1;
        for(int i = 0;i<edge1[nown].size();i++){
            int to = edge1[nown][i];
            if(!vis[to]) q.push(to);
        }
    }
    return ans-1;
}

int bfs2(int s){
    bool vis[MAXN];
    memset(vis,0,sizeof(vis));
    int ans = 0;
    queue<int> q;
    if(!q.empty()) q.pop();
    q.push(s);
    while(!q.empty()){
        int nown = q.front();q.pop();
        if(vis[nown]) continue;
        ans++;vis[nown] = 1;
        for(int i = 0;i<edge2[nown].size();i++){
            int to = edge2[nown][i];
            if(!vis[to]) q.push(to);
        }
    }
    return ans-1;
}

bool judge(int s){
    //printf("%d %d\n",bfs1(s),bfs2(s));
    return bfs1(s)+bfs2(s) == n-1;
}

void solve(){
    int cnt = 0;
    for(int i = 1;i<=n;i++){
        if(judge(i)) cnt++;
    }
    printf("%d\n",cnt);
}

int main(){
    init();
    solve();
    return 0;
}