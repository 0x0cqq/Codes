#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define int long long
using namespace std;

namespace normal_io{
    inline char read(){return getchar();}
    inline void read(int &x){scanf("%lld",&x);}
    inline void print(int x){printf("%lld",x);}
    inline void print(char x){putchar(x);}
    inline void flush(){return;}
}using namespace normal_io;

const int MAXN = 110,MAXM = 20000,MAX = 0x3f3f3f3f3f3f;

struct Edge{
    int from,to;
    int cap,flow;
    int nex,ch;
}edge[MAXM];

int n,m,s,t;
int fir[MAXN],cur[MAXN],ecnt = 2;
int dis[MAXN];

int num[MAXN],sum = 0;

void addedge(int a,int b,int c,int change){
    edge[ecnt].from = a,edge[ecnt].to = b;
    edge[ecnt].cap = c,edge[ecnt].flow = 0;
    edge[ecnt].nex = fir[a];
    edge[ecnt].ch = change;fir[a] = ecnt++;
    edge[ecnt].from = b,edge[ecnt].to = a;
    edge[ecnt].cap = 0,edge[ecnt].flow = 0;
    edge[ecnt].nex = fir[b];
    edge[ecnt].ch = 0;fir[b] = ecnt++;
}

bool bfs(){
    queue<int> q;
    memset(dis,0,sizeof(dis));
    memcpy(cur,fir,sizeof(fir));
    dis[s] = 1;q.push(s);
    while(!q.empty()){
        int nown = q.front();q.pop();
        for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
            int v = edge[nowe].to;
            if(dis[v] == 0 && edge[nowe].cap >edge[nowe].flow){
                dis[v] = dis[nown]+1,q.push(v);
                if(v == t)
                    return true;
            }
        }
    }
    return false;
}


int dfs(int nown,int limit = MAX){
    if(nown == t || limit == 0)
        return limit;
    for(int &nowe = cur[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to;
        if(dis[v] == dis[nown]+1 && edge[nowe].cap > edge[nowe].flow){
            int f = dfs(v,min(limit,edge[nowe].cap-edge[nowe].flow));
            if(f > 0){
                edge[nowe].flow += f;
                edge[nowe^1].flow -=f;
                return f;
            }
        }
    }
    return 0;
}

int dinic(){
    int ans = 0,f;
    while(bfs()){
        while((f = dfs(s)) > 0)
            ans+=f;
    }
    return ans;
}

void reset(int x){
    for(int i = 2;i<ecnt;i++){
        edge[i].flow = 0;
        if(edge[i].ch)
            edge[i].cap = x*num[edge[i].from-n];
    }
}

void init(){
    read(n),read(m);
    s = n+m+1,t = n+m+2;int tmp;
    for(int i = 1;i<=n;i++){
        read(tmp);sum+=tmp*1000;
        addedge(s,i,tmp*1000,0);
    }
    for(int i = 1;i<=m;i++){
        read(num[i]);
        addedge(n+i,t,0,1);
    }
    for(int j = 1;j<=m;j++){
        for(int i = 1;i<=n;i++){
            read(tmp);
            if(tmp) addedge(i,n+j,MAX,0);
        }
    }
}

void solve(){
    int b = 0,e = 1000000000;
    //printf("sum:%lld\n",sum);
    while(e!=b){
        int mid = (b+e)/2;
        reset(mid);
        //__print();
        int f = dinic();
        //printf("b:%lld e:%lld mid:%lld f:%lld\n",b,e,mid,f);
        //printf("\n\n");
        if(f >= sum)
            e = mid;
        else
            b = mid+1;
    }
    printf("%lf\n",double(b)/1000);
}


main(){
    init();
    solve();
    return 0;
}