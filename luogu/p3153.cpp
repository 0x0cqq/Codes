#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 200;

struct Edge{
    int from,to;
    int flow,cap;
    int nex;
    int change;
}edge[MAXN*100];

int cnt = 2;

int n,k,fir[MAXN*100],cur[MAXN*100],dis[MAXN*100],s,t;
queue<int> q;


void addedge(int a,int b,int c,bool change = 0){
    if(c == 0) return;
    edge[cnt].from = a,edge[cnt].to = b;
    edge[cnt].cap = c;edge[cnt].flow = 0;
    edge[cnt].change = change;
    edge[cnt].nex = fir[a],fir[a] = cnt++; 
    edge[cnt].from = b,edge[cnt].to = a;
    edge[cnt].cap = 0;edge[cnt].flow = 0;
    edge[cnt].nex = fir[b],fir[b] = cnt++; 
}

bool bfs(){
    memcpy(cur,fir,sizeof(cur));
    memset(dis,0,sizeof(dis));
    while(!q.empty()) q.pop();
    q.push(s);dis[s] = 1;
    while(!q.empty()){
        int nown = q.front();q.pop();
        for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
            int v = edge[nowe].to;
            if(dis[v] == 0 && edge[nowe].cap > edge[nowe].flow){
                dis[v] = dis[nown]+1;
                q.push(v);
                if(v == t){
                    return true;
                }
            }
        }
    }
    return false;//
}

int dfs(int nown,int limit = 0x3f3f3f3f){
    if(nown == t || limit == 0)
        return limit;
    for(int &nowe = cur[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to;
        if(dis[v] == dis[nown]+1 && edge[nowe].cap > edge[nowe].flow){
            int f = dfs(v,min(limit,edge[nowe].cap-edge[nowe].flow));
            if(f > 0){
                edge[nowe].flow += f;
                edge[nowe^1].flow -= f;
                return f;
            }
        }
    }
    return 0;
}

int ans = 0;

int dinic(){
    int f;
    while(bfs()){
        while((f = dfs(s)) > 0)
            ans+=f;
    }
    return ans;
}

void __print(){
    for(int i = 1;i<=4*n+2;i++){
        printf("%d:\n",i);
        for(int nowe = fir[i];nowe;nowe = edge[nowe].nex){
            printf("    to:%d flow:%d cap:%d\n",edge[nowe].to,edge[nowe].flow,edge[nowe].cap);
        }
    }
}

void change_to(int x){
    for(int i = 2;i<cnt;i++){
        if(edge[i].change)
            edge[i].cap = x;
    }
}

void init(){
    scanf("%d %d",&n,&k);
    char op[MAXN];
    for(int i = 1;i<=n;i++){
        scanf("%s",op+1);
        for(int j = 1;j<=n;j++){
            if(op[j] == 'Y'){
                addedge(2*i-1,2*n+2*j-1,1);
            }else{
                addedge(2*i,2*n+2*j,1);
            }
        }
    }
    s = 4*n+1,t = 4*n+2;
    for(int i = 1;i<=n;i++){
        addedge(2*i-1,2*i,k);
        addedge(2*n+2*i,2*n+2*i-1,k);
        addedge(s,2*i-1,1,1);
        addedge(2*n+2*i-1,t,1,1);
    }
}

void solve(){
    for(int i = 1;i<=n+1;i++){
        change_to(i);
        dinic();
        //__print();
        //printf("i:%d f:%d\n",i,ans);
        if(ans < i*n){
            printf("%d\n",i-1);
            break;
        }
    }
}

int main(){
    init();
    solve();
    return 0;
}