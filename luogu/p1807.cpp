#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 110000;

int dis[MAXN];
bool instack[MAXN];

struct Edge{
    int to,len;
};

int n,m;

vector<Edge> edge[MAXN];

void spfa(){
    queue<int> q;
    q.push(1);
    memset(instack,0,sizeof(instack));
    memset(dis,0x3f,sizeof(dis));
    dis[1] = 0;
    instack[1] = 1;
    while(!q.empty()){
        int nown = q.front();q.pop();
        instack[nown] = 0;
        for(int i = 0;i<edge[nown].size();i++){
            int t = edge[nown][i].to,l = edge[nown][i].len;
            if(dis[nown]+l<dis[t]){
                dis[t] = dis[nown]+l;
                if(!instack[t]){
                    q.push(t);
                    instack[t] = 1;
                }
            }
        }
    }
}

void addedge(int u,int v,int l){
    Edge a;
    a.to = v,a.len = -l;
    edge[u].push_back(a);
}

void solve(){
    scanf("%d %d",&n,&m);
    int a,b,c;
    for(int i = 1;i<=m;i++){
        scanf("%d %d %d",&a,&b,&c);
        addedge(a,b,c);
    }
    spfa();
    if(dis[n]>100000000)
        printf("-1\n");
    else
        printf("%d\n",-dis[n]);
}

int main(){
    solve();
    return 0;
}