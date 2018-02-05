#include <cstdio>
#include <unistd.h>
#include <queue>
#include <cstring>
#include <algorithm>
#define maxint 2147483647
using namespace std;

void qr(int &x){
    x = 0;char ch = getchar();
    while(ch<'0'||ch>'9')
        ch = getchar();
    while(ch>='0'&&ch<='9')
        x = (x<<3)+(x<<1)+ch-48,ch = getchar();
}

int from[300000],to[300000];
int flow[300000],cap[300000];
int next_e[300000];
int first[110000],cur[110000];
int dis[110000];

queue<int> q;

int n,m,s,t,poolcnt = 2;

int bfs(){
    while(!q.empty()) q.pop();
    memset(dis,0,sizeof(dis));
    memcpy(cur,first,sizeof(cur));
    q.push(s);
    while(!q.empty()){
        int nown = q.front();q.pop();
        for(int e = first[nown];e;e = next_e[e]){
            if(cap[e] > flow[e] && dis[to[e]] == 0 && to[e]!=s){
                dis[to[e]] = dis[nown]+1;
                q.push(to[e]);
                if(to[e] == t)
                    break;
            }
        }
    }
    return dis[t];
}

int dfs(int nown,int limit = maxint){
    if(limit == 0)
        return 0;
    if(nown == t) return limit;
    int f = 0;
    for(int &e = cur[nown];e;e = next_e[e]){
        if(dis[to[e]]!=dis[nown]+1) continue;
        if((f = dfs(to[e],min(limit,cap[e] - flow[e])))>0){
            flow[e] += f,flow[e^1] -= f;
            return f;
        }
    }
    return 0;
}

void addedge(int u,int v,int c){
    int newe = poolcnt++;
    from[newe] = u,to[newe] = v,cap[newe] = c;
    next_e[newe] = first[u],first[u] = newe;
    newe = poolcnt++;
    from[newe] = v,to[newe] = u,cap[newe] = 0;
    next_e[newe] = first[u],first[u] = newe;
}

int dinic(){
    int ans = 0,f = 0;
    while(bfs())
        while((f = dfs(s))!=0) ans+=f;
    return ans;
}

int main(){
    freopen("1.in","r",stdin);
    qr(n),qr(m),qr(s),qr(t);
    for(int i = 0;i<m;i++){
        int a,b,c;
        qr(a),qr(b),qr(c);
        addedge(a,b,c);
    }
    printf("%d\n",dinic());
    return 0;
}