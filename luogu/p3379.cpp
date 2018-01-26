#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> edge[510000];

int n,m,f[510000][20],deep[510000],vis[510000],bin[20],maxb,s;

int qr(){
    int f = 1,s = 0;char c = getchar();
    while(c<'0'||c>'9'){
        if(c == '-') f = -1;
        c = getchar();
    }
    while(c>='0'&&c<='9'){
        s = (s<<3)+(s<<1)+c-48;
        c = getchar();
    }
    return f*s;
}

void pre_bin(){
    maxb = 0;int t = 1;
    while(t<=n)
        t<<=1,maxb++;
    t = 1;
    for(int i = 0;i<20;i++){
        bin[i] = t;
        t<<=1;
    }
}

void pre_dfs(int nown,int depth){
    deep[nown] = depth;
    vis[nown] = 1;
    for(int i:edge[nown]){
        if(vis[i]) continue;
        f[i][0] = nown;
        pre_dfs(i,depth+1);
    }
}

void pre_lca(){
    for(int j = 1;j<maxb;j++)
        for(int i = 1;i<=n;i++)
            if(bin[j] <= deep[i])
                f[i][j] = f[ f[i][j-1] ][j-1];
}

int find_lca(int u,int v){
    if(deep[u]<deep[v]) swap(u,v);
    for(int i = maxb-1;i>=0;i--)
        if(deep[f[u][i]]>=deep[v])
            u = f[u][i];
    if(u == v) return u;
    for(int i = maxb-1;i>=0;i--)
        if(f[u][i]!=f[v][i])
            u = f[u][i],v = f[v][i];
    return f[u][0];
}



int main(){
    scanf("%d %d %d",&n,&m,&s);
    for(int i = 1;i<=n-1;i++){
        int a,b;
        a = qr();b =qr();
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    deep[0] = -1;
    pre_dfs(s,0);
    pre_bin();
    pre_lca();
    for(int i = 1;i<=m;i++){
        int a,b;
        a =qr(); b = qr();
        printf("%d\n",find_lca(a,b));
    }
    
    return 0;
}