#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 110000,MAXM = 200000;

struct Edge{
    int from,to;
    int cap,flow;
    int nex;
}edge[MAXM];

int n,m,s,t,ecnt = 2;

int fir[MAXN],cur[MAXN];

void addedge(int a,int b,int c){
    edge[ecnt] = (Edge){a,b,c,0,fir[a]};
    fir[a] = ecnt++;
    edge[ecnt] = (Edge){b,a,0,0,fir[a]};
    fir[b] = ecnt++;
}

int dis[MAXN];

queue<int> q;

bool bfs(){
    memset(dis,0,sizeof(dis));
    while(!q.empty()) q.pop();
    dis[s] = 1;q.push(s);
    while(!q.empty()){
        int nown = q.front();q.pop();
        for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
            int v = edge[nowe].to;
            if(dis[v] == 0 && edge[nowe].cap >edge[nowe].flow){
                dis[v] = dis[nown] + 1;
                q.push(v);
                if(v == t)
                    return 1;
            }
        }
    }
    return 0;
}



int dfs(int nown,int limit = 0x3f3f3f3f){
    if(nown == t || limit == 0)
        return limit;
    for(int &nowe = cur[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to;
        if(dis[v] == dis[nown] + 1 && edge[nowe].cap > edge[nowe].flow){
            int f = dfs(v,min(limit,edge[nowe].cap - edge[nowe].flow));
            if(f){
                edge[nowe].flow += f;
                edge[nowe].flow -=f;
                return f;
            }
        }
    }
    return 0;
}


int dinic(){
    int ans = 0,f = 0;
    while(bfs()){
        while((f = dfs(s)) > 0){
            ans +=f;
        }
    }
    return ans;
}

void init(){
    read(n);
    
}

int main(){
    return 0;
}