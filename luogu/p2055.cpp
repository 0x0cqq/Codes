#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge{
    int from,to,cap,flow;
    int next;
}edge[10000];

int fir[10000],cur[10000];

int w,n,nowe,dis[200],s,t;
bool is_school[200],is_home[200];

void addedge(int from,int to,int c){
    //from的范围：1~n,to的范围：n+1~2n;
    edge[nowe].from = from;edge[nowe].to = to;
    edge[nowe].flow = 0;edge[nowe].cap = c;
    edge[nowe].next = fir[from];fir[from] = nowe;
    nowe++;
}

int bfs(){
    memcpy(cur,fir,sizeof(cur));
    memset(dis,-1,sizeof(dis));
    queue<int> q;
    dis[s] = 0;
    q.push(s);
    while(!q.empty()){
        int nown = q.front();q.pop();
        for(int i = fir[nown];i!=-1;i = edge[i].next){
            int v = edge[i].to;
            if(dis[v] == -1 && v != s && edge[i].cap>edge[i].flow){
                dis[v] = dis[nown]+1;
                q.push(v);
            }
            if(v == t) break;
        }
    }
    return dis[t];
}

int dfs(int nown,int limit = 0x3f3f3f3f){
    if(limit == 0) return 0;
    if(nown == t) return limit;
    int f = 0;
    for(int &e = cur[nown];e!=-1;e = edge[e].next){
        if(dis[edge[e].to]!=dis[nown]+1) continue;
        if((f = dfs(edge[e].to,min(limit,edge[e].cap - edge[e].flow)))>0){
            edge[e].flow += f;
            edge[e^1].flow -= f;
            return f;
        }
    }
    return 0;
}

void print(){
    for(int i = 1;i<=2*n+2;i++)
        printf("%d:%d ",i,dis[i]);
    putchar('\n');
    for(int i = 0;i<nowe;i++){
        printf("u:%d v:%d f:%d c:%d\n",edge[i].from,edge[i].to,edge[i].flow,edge[i].cap);
    }
    sleep(2);
}

int dinic(){
    int ans = 0;
    while(bfs()!=-1){
        int f;
        while((f = dfs(0))!=0)
            ans+=f;
        printf("ANS:%d\n",ans);
        print();
    }
    return ans;
}

int main(){
    scanf("%d",&w);
    for(int k = 0;k<w;k++){
        nowe = 0;
        memset(edge,0,sizeof(edge));
        memset(fir,-1,sizeof(fir));
        memset(cur,-1,sizeof(cur));
        scanf("%d",&n);
        s = 2*n+1,t = 2*n+2;
        int cnt = n;
        for(int i = 1;i<=n;i++){
            cin >> is_school[i];
        }
        for(int i = 1;i<=n;i++){
            cin >> is_home[i];
            if(is_school[i] == 0) is_home[i] = 0;
            if(is_home[i]) cnt--;
        }
        for(int i = 1;i<=n;i++){
            for(int j = 1;j<=n;j++){
                int w;scanf("%d",&w);
                if(i == j) w = 1;
                if(is_home[i] == 0 && is_school[j] == 1&&w == 1)
                    addedge(i,j+n,1),addedge(j+n,i,0);
                printf("i:%d,j:%d:  %d %d %d:::%d\n",i,j,is_home[i],is_school[j],w,is_home[i] == 0 && is_school[j] == 1&&w == 1);
                sleep(1);
            }
        }
        sleep(10);
        for(int i = 1;i<=n;i++){
            if(is_home[i] != 1)   addedge(s,i,1),addedge(i,s,0);
            if(is_school[i] != 0) addedge(i+n,t,1),addedge(t,i+n,0);
        }
        //print();
        //printf("CNT:%d\n",cnt);
        printf("!\n");
        if(dinic() >= cnt)
            printf("^_^\n");
        else
            printf("T_T\n");
    }
    return 0;
}