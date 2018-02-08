#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

struct Edge{
    int from,to,flow,cap;
    int next;
}edge[201000];
int fir[10100],dis[10100],cur[10100];

int n,m,s,t,tot = 2;

bool bfs(){
    queue<int> q;
    memset(dis,0,sizeof(dis));
    memcpy(cur,fir,sizeof(fir));
    q.push(s);dis[s] = 1;
    while(!q.empty()){
        int nown = q.front();q.pop();
        for(int nowe = fir[nown];nowe!=0;nowe = edge[nowe].next){
            int v = edge[nowe].to;
            if(dis[v] == 0 && edge[nowe].cap > edge[nowe].flow){
                dis[v] = dis[nown]+1;
                q.push(v);
                if(v == t)
                    return dis[t];
            }
        }
    }
    return dis[t];
}

int dfs(int nown,int limit = 0x3f3f3f3f){
    if(nown == t || limit == 0)
        return limit;
    for(int &nowe = cur[nown];nowe!=0;nowe = edge[nowe].next){
        int v = edge[nowe].to;
        if(dis[v] == dis[nown]+1 && edge[nowe].flow < edge[nowe].cap){
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
    edge[tot].from = a;edge[tot].to = b;
    edge[tot].cap = c;edge[tot].flow = 0;
    edge[tot].next = fir[a];fir[a] = tot;
    tot++;
}

int main(){
    scanf("%d %d %d %d",&n,&m,&s,&t);
    for(int i = 0;i<m;i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        addedge(a,b,c);
        addedge(b,a,0);
    }
    printf("%d\n",dinic());
    return 0;
}