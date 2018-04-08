#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 200,MAXM = 3000;
const double eps = 1e-6;

struct Edge{
    int from,to;
    double cap,flow,f_c;
    int nex;
}edge[MAXM];

int n,m,s,t,p;
int fir[MAXN],cur[MAXN],ecnt = 2;

double max_flow;

void addedge(int a,int b,int c){
    edge[ecnt].from = a,edge[ecnt].to = b;
    edge[ecnt].cap = edge[ecnt].f_c = c;
    edge[ecnt].nex = fir[a],fir[a] = ecnt++;
    edge[ecnt].from = b,edge[ecnt].to = a;
    edge[ecnt].cap = edge[ecnt].f_c = 0;
    edge[ecnt].nex = fir[b],fir[b] = ecnt++;  
}

int dis[MAXN];
queue<int> q;

bool bfs(){
    while(!q.empty()) q.pop();
    memset(dis,0,sizeof(dis));
    memcpy(cur,fir,sizeof(fir));
    dis[s] = 1;q.push(s);
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
    return false;
}


double dfs(int nown,double limit = 1e9){
    if(nown == t || limit < eps)
        return limit;
    for(int &nowe = cur[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to;
        if(dis[v] == dis[nown]+1 && edge[nowe].cap > edge[nowe].flow){
            double f = dfs(v,min(limit,edge[nowe].cap - edge[nowe].flow));
            if(f > eps){
                edge[nowe].flow+=f;
                edge[nowe^1].flow-=f;
                return f;
            }
        }
    }
    return 0;
}

double dinic(){
    double ans = 0,f;
    while(bfs()){
        while((f = dfs(s)) > eps){
            ans+=f;
            //printf("%lf!!!\n",f);
        }
    }
    return ans;
}

void set(double a){
    for(int nowe = 2;nowe<ecnt;nowe++){
        edge[nowe].flow = 0,edge[nowe].cap = edge[nowe].f_c;
        if(edge[nowe].cap > a)
            edge[nowe].cap = a;
    }
}

void init(){
    scanf("%d %d %d",&n,&m,&p);
    s = 1,t = n;
    int a,b,c;
    for(int i = 1;i<=m;i++){
        scanf("%d %d %d",&a,&b,&c);
        addedge(a,b,c);
    }
    max_flow = dinic();
}

void solve(){
    //printf("%lf\n",max_flow);
    double b = 0,e = 100000;
    while(e-b>1e-5){
        double mid = (b+e)/2;
        set(mid);
        //printf("%lf %lf mid:%lf\n",b,e,mid);
        double t =  dinic();
        //printf("    f:%lf\n",t);
        if(t == max_flow)
            e = mid;
        else
            b = mid;
    }
    printf("%d\n%.4lf\n",int(max_flow),double(b)*double(p));
}

int main(){
    init();
    solve();
    return 0;
}