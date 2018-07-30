#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 11000;

vector<int> edge[MAXN];
int n,m;
int col[MAXN];
bool vis[MAXN];

void init(){
    scanf("%d %d",&n,&m);
    int u,v;
    for(int i = 1;i<=m;i++){
        scanf("%d %d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
}

bool dfs1(int x,int fa){
    col[x] = col[fa]^1;
    for(int i = 0;i<edge[x].size();i++){
        int v = edge[x][i];
        if(v == fa) continue;
        if(col[v] == -1){
            if(!dfs1(v,x)) return false;
        }
        else{
            if(!(col[x]^col[v])) return false; 
        }
    }
    return true;
}

pair<int,int> dfs2(int x,int fa){
    vis[x] = 1;
    pair<int,int> ans = make_pair(0,0);
    if(col[x]) ans.second += 1;
    else ans.first += 1;
    for(int i = 0;i<edge[x].size();i++){
        int v = edge[x][i];
        if(v == fa || vis[v]) continue;
        pair<int,int> tmp = dfs2(v,x);
        ans.first += tmp.first,ans.second += tmp.second;
    }
    return ans;
}

int solve(){
    int ans = 0;
    for(int i = 1;i<=n;i++) col[i] = -1;
    for(int i = 1;i<=n;i++){
        if(col[i] == -1){
            bool f = dfs1(i,0);
            if(!f) return -1;
            pair<int,int> tmp = dfs2(i,0);
            ans += min(tmp.first,tmp.second);
        }
    }
    return ans;
}

int main(){
    init();
    int t = solve();
    if(t == -1){
        printf("Impossible\n");
    }
    else{
        printf("%d\n",t);
    }
    return 0;
}