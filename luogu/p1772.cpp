#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 21;

struct Edge{
    int to,len;
    Edge(int t = 0,int l = 0):to(t),len(l){};
};

bool disable[MAXN][MAXN<<3];

vector<Edge> edge[MAXN];

void addedge(int a,int b,int c){
    edge[a].push_back(Edge(b,c));
    edge[b].push_back(Edge(a,c));
}

int n,m,k,e,d;

void init(){
    scanf("%d %d %d %d",&n,&m,&k,&e);
    int a,b,c;
    for(int i = 1;i<=e;i++){
        scanf("%d %d %d",&a,&b,&c);
        addedge(a,b,c);
    }
    scanf("%d",&d);
    for(int i = 1;i<=d;i++){
        scanf("%d %d %d",&a,&b,&c);
        for(int j = b;j<=c;j++){
            disable[a][j] = 1;
        }
    }
}

bool jjj[MAXN][MAXN<<3][MAXN<<3];

void judge(){
    for(int point = 1;point<=m;point++)
    for(int l = 1;l<=n;l++)
    for(int r = l;r<=n;r++)
    for(int i = l;i<=r;i++){
        if(disable[point][i]){
            jjj[point][l][r] = true;
            break;
        }
    }
}

int spfa(int l,int r){
    int dis[MAXN];bool instack[MAXN];
    queue<int> q;
    memset(dis,0x3f,4*m+4);
    memset(instack,0,4*(m+1));
    dis[1] = 0;q.push(1);
    while(!q.empty()){
        int nown = q.front();q.pop();
        instack[nown] = 0;
        for(int i = 0;i<edge[nown].size();i++){
            int to = edge[nown][i].to,len = edge[nown][i].len;
            if(jjj[to][l][r]) continue;
            if(dis[to] > dis[nown] + len){
                dis[to] = dis[nown]+len;
                if(!instack[to]){
                    q.push(to);
                    instack[to] = 1;
                }
            }
        }
    }
    return dis[m]>100000?100000:dis[m];
}

void dd(){
    int dp[MAXN<<3];
    memset(dp,0x3f,4*n+4);
    dp[0] = 0;
    for(int i = 1;i<=n;i++)
        for(int j = 0;j<i;j++)
            dp[i] = min(dp[i],dp[j]+spfa(j+1,i) * (i-j) + k);
    printf("%d\n",dp[n]-k);
}

int main(){
    init();
    judge();
    dd();
    return 0;
}