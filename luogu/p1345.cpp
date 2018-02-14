#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

struct Edge{
    int from,to,cap,flow;
    int next;
}edge[500]; 

int fir[210],cur[210],dis[210],cnt;

int n,m,s,t;

inline bool bfs(){
    queue<int> q;
    memset(dis,0,sizeof(dis));
    memcpy(cur,fir,sizeof(cur));
    q.push(s);dis[s] = 1;
    while(!q.empty()){
        int nown = q.front();q.pop();
        for(int e = fir[nown];e;e = edge[e].next){
            int v = edge[e].to;
            if(dis[v] == 0 && edge[e].cap  > edge[e].flow){
                dis[v] = dis[nown]+1;
                q.push(v);
                if(v == t)
                    return dis[t]; 
            }
        }
    }
    return dis[t];
}

inline int dfs(int nown,int limit){
    if(nown == t || limit == 0)
        return limit;
    for(int &e = cur[nown];e;e = edge[e].next){
        int v = edge[e].to;
        if(dis[v] == dis[nown]+1 && edge[e].cap > edge[e].flow){
            int f = dfs(v,min(limit,edge[e].cap - edge[e].flow));
            if(f>0){
                edge[e].flow+=f;
                edge[e^1].flow-=f;
                return f;
            }
        }
    }
    return 0;
}

inline int dinic(){
    int ans = 0,f;
    while(bfs()){
        while((f = dfs(s,0x3f3f3f3f)>0)){
            ans += f;
        }
    }
    return ans;
}

inline void addedge(int a, int b, int c){
    edge[cnt].from = a,edge[cnt].to = b;
    edge[cnt].cap = c,edge[cnt].flow = 0;
    edge[cnt].next = fir[a],fir[a] = cnt;
    cnt++;
    edge[cnt].from = b,edge[cnt].to = a;
    edge[cnt].cap = 0,edge[cnt].flow = 0;
    edge[cnt].next = fir[b],fir[b] = cnt;
    cnt++;
}

inline void init(){
    cnt = 2;
    scanf("%d %d %d %d",&n,&m,&s,&t);
    t+=n;
    for(int i = 1;i<=m;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        addedge(a,b+n,1);
        addedge(b,a+n,1);
    }
    for(int i = 1;i<=n;i++){
        addedge(i+n,i,1);
    }
}

inline void solve(){
    printf("%d\n",dinic());
}

int main(){
    init();
    solve();
    return 0;
}