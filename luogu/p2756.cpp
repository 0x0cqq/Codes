/*
    Luogu p2756
    2018-02-10 14:00:29
    0ms, 1882KB
*/
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
#include <unistd.h>
using namespace std;

struct Edge{
    int from,to;
    int flow,cap;
    int next;
}edge[2500];

int fir[102],cur[102],dis[102],s,t,n,m,cnt = 2;

queue<int> q;

bool bfs(){
    while(!q.empty()) q.pop();
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
                if(v == t)
                    return dis[t];
            }
        }
    }
    return dis[t];
}


int dfs(int nown,int limit){
    if(nown == t || limit == 0){
        return limit;
    }
    for(int &e = cur[nown];e!=0;e = edge[e].next){
        int v = edge[e].to;
        if(dis[v] == dis[nown]+1 && edge[e].cap > edge[e].flow){
            int f = dfs(v,min(limit,edge[e].cap-edge[e].flow));
            if(f>0){
                edge[e].flow+=f;
                edge[e^1].flow-=f;
                return f;
            }
        }
    }
    return 0;
}

int dinic(){
    int ans = 0,f;
    while(bfs()){
        while((f = dfs(s,0x3f3f3f3f))>0){
            ans+=f;
        }
        //printf("%d\n",ans);
        //sleep(1);
    }
    return ans;
}

void addedge(int a,int b,int c){
    edge[cnt].from = a,edge[cnt].to = b;
    edge[cnt].cap = c,edge[cnt].flow = 0;
    edge[cnt].next = fir[a],fir[a] = cnt;
    cnt++;
    edge[cnt].from = b,edge[cnt].to = a;
    edge[cnt].cap = 0,edge[cnt].flow = 0;
    edge[cnt].next = fir[b],fir[b] = cnt;
    cnt++;
}

int main(){
    scanf("%d %d",&m,&n);
    s = n+1,t = n+2;
    int a,b,w = 2;
    while(true){
        scanf("%d %d",&a,&b);
        if(a == -1||b == -1)
            break;
        addedge(a,b,1);
        w+=2;
    }
    for(int i = 1;i<=m;i++){
        addedge(s,i,1);
    }
    for(int i = m+1;i<=n;i++){
        addedge(i,t,1);
    }
    int ans = dinic();
    if(ans>0){
        printf("%d\n",ans);
        for(int i = 2;i<w;i++){
            if(edge[i].flow>0){
                printf("%d %d\n",edge[i].from,edge[i].to);
            }
        }   
    }
    else{
        printf("No Solution!");
    }
    return 0;
}