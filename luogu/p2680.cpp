#include <cstdio>
#include <algorithm>
#include <cctype>
#include <vector>
#define pp pair<int,int>
using namespace std;

namespace normal_io{
    inline char read(){return getchar();}
    inline void read(int &x){scanf("%d",&x);}
    inline void read(char *x){scanf("%s",x);}
    inline void print(int x){printf("%d",x);}
    inline void print(char x){putchar(x);}
    inline void flush(){return;}
}using namespace normal_io;

const int MAXN = 310000;
int n,m;

struct Edge{
    int to,len;
    Edge(int a,int b):to(a),len(b){};
};

vector<Edge> edge[MAXN];

int u[MAXN],v[MAXN];

//
int siz[MAXN],son[MAXN],fa[MAXN],dep[MAXN],top[MAXN];
void dfs1(int nown,int f,int depth){
    siz[nown] += 1,fa[nown] = f;
    dep[nown] = depth;
    for(int i = 0;i<edge[nown].size();i++){
        int v = edge[nown][i].to,l = edge[nown][i].len;
        if(v == fa[nown]) continue;
        dfs1(v,nown,depth+1);
        siz[nown] += siz[v];
        if(siz[v] > siz[son[nown]]) son[nown] = v;
    }
}
void dfs2(int nown,int topf){
    top[nown] = topf;
}
//

void init(){
    read(n),read(m);
    int a,b,c;
    for(int i = 1;i<=n;i++){
        read(a),read(b),read(c);
        edge[a].emplace_back(a,c);
        edge[b].emplace_back(b,c);
    }
    for(int i = 1;i<=m;i++){
        read(u[i]),read(v[i]);
    }
}

int main(){
    return 0;
}