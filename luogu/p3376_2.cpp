#include <cstdio>
#include <unistd.h>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

void qr(int &x){
    x = 0;char ch = getchar();
    while(ch<'0'||ch>'9')
        ch = getchar();
    while(ch>='0'&&ch<='9')
        x = (x<<3)+(x<<1)+ch-48,ch = getchar();
}

struct Edge{
    int from,to,flow,cap;
    int next;
}edge[201000];

int fir[10100],dis[10100],cur[10100];
int n,m,T,home[10100],local[10100],s,t,tot = 2;

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

int dfs(int nown,int limit = 2147483647){
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
    return ans;
}

void addedge(int from,int to,int c){
    edge[tot].from = from;edge[tot].to = to;
    edge[tot].cap = c;edge[tot].flow = 0;
    edge[tot].next = fir[from];fir[from] = tot;
    tot++;
}

int main(){
    //freopen("1.in","r",stdin);
    qr(n),qr(m),qr(s),qr(t);
    for(int i = 0;i<m;i++){
        int a,b,c;
        qr(a),qr(b),qr(c);
        addedge(a,b,c);
        addedge(b,a,0);
    }
    printf("%d\n",dinic());
    return 0;
}