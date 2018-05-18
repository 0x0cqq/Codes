#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

namespace normal_io{
    inline char read(){return getchar();}
    inline void read(int &x){scanf("%d",&x);}
    inline void read(char *x){scanf("%s",x);}
    inline void print(int x){printf("%d",x);}
    inline void print(char x){putchar(x);}
    inline void flush(){return;}
}using namespace normal_io;

const int MAXN = 210000;

int n;

struct TRI{
    int a,b;
    int id;
    bool operator < (TRI o)const{
        if(a != o.a) return a < o.a;
        else return b < o.b;
    }
};

vector<TRI> S;

vector<int> edge[MAXN];


void init(){
    read(n);
    int a,b,c;
    for(int i = 1;i<=n-2;i++){
        read(a),read(b),read(c);
        S.push_back((TRI){min(a,b),max(a,b),i});
        S.push_back((TRI){min(b,c),max(b,c),i});
        S.push_back((TRI){min(a,c),max(a,c),i});
    }
}

void build(){
    sort(S.begin(),S.end());
    for(int i = 1;i < S.size();i++){   
        if(S[i].a == S[i-1].a && S[i].b == S[i-1].b){
            int u = S[i].id,v = S[i-1].id;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
    }
}

int dis[MAXN];

void dfs(int nown,int fa){
    for(int i = 0;i<edge[nown].size();i++){
        int v = edge[nown][i];
        if(v == fa) continue;
        dis[v] = dis[nown] + 1;
        dfs(v,nown);
    }
}

void solve(){
    memset(dis,0,sizeof(dis));
    dfs(1,0);
    int u = 0,v = 0;
    for(int i = 1;i<=n-2;i++){
        if(dis[i] > dis[u])
            u = i;
    }
    memset(dis,0,sizeof(dis));
    dfs(u,0);
    for(int i = 1;i<=n-2;i++){
        if(dis[i] > dis[v])
            v = i;
    }
    printf("%d\n",dis[v]+1);
}

int main(){
    init();
    build();
    solve();
    return 0;
}