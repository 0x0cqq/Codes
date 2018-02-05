#include <cstdio>
#include <unistd.h>
#include <queue>
#include <cstring>
#include <algorithm>
#define maxint 2147483647
using namespace std;

struct Edge{
    int from,to;
    int flow,cap;
    Edge *next,*rev;
}pool[300000];

Edge *first[110000],*cur[110000];
queue<int> q;
int dis[110000];

int n,m,s,t,poolcnt = 0;

int bfs(){
    while(!q.empty()) q.pop();
    memset(dis,0,sizeof(dis));
    memcpy(cur,first,sizeof(cur));
    q.push(s);//dis[s] = 0;
    while(!q.empty()){
        int nown = q.front();q.pop();
        for(Edge *e = first[nown];e!= NULL;e = e->next){
            if(e->cap > e->flow && dis[e->to] == 0 && e->to!=s){
                dis[e->to] = dis[nown]+1;
                q.push(e->to);//可能需要特判终点
                if(e->to == t)
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
    for(Edge *&e = cur[nown];e!=NULL;e = e->next){
        if(dis[e->to]!=dis[nown]+1) continue;
        if((f = dfs(e->to,min(limit,e->cap - e->flow)))>0){
            e->flow += f;
            e->rev->flow -= f;
            return f;
        }
    }
    return 0;
}

void print(){
    for(int i = 1;i<=n;i++)
        printf("%d:%d ",i,dis[i]);
    putchar('\n');
    for(int i = 0;i<poolcnt;i++){
        printf("u:%d v:%d f:%d c:%d\n",pool[i].from,pool[i].to,pool[i].flow,pool[i].cap);
    }
}


void addedge(int u,int v,int cap){
    Edge *newe = &pool[poolcnt++];
    newe->from = u,newe->to = v,newe->cap = cap;
    newe->next = first[u],first[u] = newe;

    Edge *reve = &pool[poolcnt++];
    reve->from = v,reve->to = u,reve->cap = 0;
    reve->next = first[v],first[v] = reve;

    reve->rev = newe,newe->rev = reve;
}

int dinic(){
    int ans = 0,f = 0;
    while(bfs()){
        //printf("finished bfs\n");
        while((f = dfs(s))!=0)
            ans+=f;
        //printf("%d\n",ans);
        //print();
        //sleep(10);
    }
    return ans;
}

int main(){
    //freopen("1.in","r",stdin);
    scanf("%d %d %d %d",&n,&m,&s,&t);
    for(int i = 0;i<m;i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        addedge(a,b,c);
    }
    printf("%d\n",dinic());
    return 0;
}