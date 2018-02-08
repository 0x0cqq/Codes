#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int dis[2500],s,t,n,m,e,cnt = 2;

struct Edge{
    int from,to;
    int flow,cap;
    int next;
}edge[100000];

int fir[2500],cur[2500];

bool bfs(){
    queue<int> q;
    memset(dis,0,sizeof(dis));
    memcpy(cur,fir,sizeof(fir));
    q.push(s);dis[s] = 1;
    while(!q.empty()){
        int nown = q.front();q.pop();
        for(int nowe = fir[nown];nowe!=0;nowe = edge[nowe].next){
            int v = edge[nowe].to;
            if(dis[v] == 0&&edge[nowe].flow <edge[nowe].cap){
                dis[v] = dis[nown]+1;
                q.push(v);
            }
        }
    }
    return dis[t];
}

int dfs(int nown,int limit = 0x3f3f3f3f){
    if(nown == t||limit == 0)
        return limit;
    for(int &nowe = cur[nown];nowe!=0;nowe = edge[nowe].next){
        int v = edge[nowe].to;
        if(dis[v] == dis[nown]+1&&edge[nowe].flow <edge[nowe].cap){
            int f = dfs(v,min(edge[nowe].cap-edge[nowe].flow,limit));
            if(f>0){
                edge[nowe].flow+=f;
                edge[nowe^1].flow-=f;
                return f;
            }
        }
    }
    return 0;
}

int dinic(){
    int ans = 0,f;
    while(bfs()){
        while((f = dfs(s))>0) 
            ans+=f;
    }
    return ans;
}

void addedge(int a,int b,int c){
    edge[cnt].from = a,edge[cnt].to = b,edge[cnt].cap = c;
    edge[cnt].next = fir[a],fir[a] = cnt;
    cnt++;
}

int main(){
    scanf("%d %d %d",&n,&m,&e);
    s = n+m+1,t = n+m+2;
    for(int i = 1;i<=e;i++){
        int a,b;scanf("%d %d",&a,&b);
        if(a>n||b>m) continue;
        else{
            addedge(a,n+b,1);
            addedge(n+b,a,0);
        }
    }
    for(int i = 1;i<=n;i++){
        addedge(s,i,1);
        addedge(i,s,0);        
    }
    for(int i = 1;i<=m;i++){
        addedge(i+n,t,1);
        addedge(t,i+n,0);
    }
    printf("%d\n",dinic());
    return 0;
}