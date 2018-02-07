#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge{
    int from,to,flow,cap;
    int next;
}edge[20000];

int fir[300],dis[300],cur[300];
int n,T,home[300],local[300],s,t,tot;

bool bfs(){
    queue<int> q;
    memset(dis,0,sizeof(dis));
    memcpy(cur,fir,sizeof(fir));
    q.push(s);dis[s] = 1;
    while(!q.empty()){
        int nown = q.front();q.pop();
        for(int e = fir[nown];e!=0;e = edge[e].next){
            int v = edge[e].to;
            if(dis[v] == 0 && edge[e].cap > edge[e].flow){
                dis[v] = dis[nown]+1;
                q.push(v);
            }
        }
    }
    return dis[t];
}

int dfs(int nown,int limit = 0x3f3f3f3f){
    if(nown == t) return limit;
    if(limit == 0) return 0;
    int fff = 0;
    for(int &e = cur[nown];e!=0;e = edge[e].next){
        int f,v = edge[e].to;
        if(dis[v] == dis[nown]+1 && (f = dfs(v,min(limit,edge[e].cap-edge[e].flow)))>0){
            edge[e].flow+=f;
            edge[e^1].flow-=f;
            limit-=f,fff+=f;
            if(limit == 0) break;
        }
    }
    return fff;
}

void print(){
    for(int i = 1;i <= t;i++)
        printf("i:%d dis:%d,cur:%d\n",i,dis[i],cur[i]);
    for(int i = 0;i<tot;i++)
        printf("u:%d v:%d f:%d c:%d\n",edge[i].from,edge[i].to,edge[i].flow,edge[i].cap);
}

int dinic(){
    int ans = 0;
    while(bfs()){
        ans += dfs(s);
        //printf("ANS:%d\n",ans);print();sleep(2);
    }
    printf("%d\n",ans);
    return ans;
}

void addedge(int from,int to,int c){
    edge[tot].from = from;edge[tot].to = to;
    edge[tot].cap = c;edge[tot].flow = 0;
    edge[tot].next = fir[from];fir[from] = tot;
    tot++;
}

int main(){
    freopen("1.in","r",stdin);
    scanf("%d",&T);
    for(int i = 1;i<=T;i++){
        scanf("%d",&n);
        memset(edge,0,sizeof(edge));
        memset(home,0,sizeof(home));
        memset(local,0,sizeof(local));
        memset(fir,0,sizeof(fir));
        tot = 2;int cnt = 0;
        s = 2*n+1,t = 2*n+2;
        for(int i = 1;i<=n;i++){
            scanf("%d",&local[i]);
        }
        for(int i = 1;i<=n;i++){
            scanf("%d",&home[i]);
            if(local[i] == 0) home[i] = 0;
        }
        for(int i = 1;i<=n;i++){
            for(int j = 1;j<=n;j++){
                int tmp;scanf("%d",&tmp);
                if(i == j) tmp = 1;
                if(home[i] == 1||local[j] == 0||tmp == 0) continue;
                else addedge(i,j+n,1),addedge(j+n,i,0);
            }
        }
        for(int i = 1;i<=n;i++){
            if(home[i] == 0)
                addedge(s,i,1),addedge(i,s,0),cnt++;
            if(local[i] == 1)
                addedge(i+n,t,1),addedge(t,i+n,0);
        }
        if(dinic()>=cnt) printf("^_^\n");
        else printf("T_T\n");
    }
    return 0;
}