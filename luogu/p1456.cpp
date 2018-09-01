// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000;

namespace MergeHeap{
int val[MAXN],lc[MAXN],rc[MAXN],d[MAXN];
void init(int n,int *num){
    for(int i = 1;i<=n;i++)
        val[i] = num[i],lc[i] = rc[i] = d[i] = 0;
}
int merge(int x,int y){
    if(x == y) return x;
    if(!x || !y) return x+y;
    if(val[x] < val[y]) swap(x,y);
    rc[x] = merge(rc[x],y);
    if(d[rc[x]] > d[lc[x]])
        swap(lc[x],rc[x]);
    d[x] = d[rc[x]] + 1;
    return x;
}
int top(int x){
    return val[x];
}
int del(int x){
    int t = merge(lc[x],rc[x]);
    lc[x] = rc[x] = 0;
    return t;
}
void print(int n){
    printf("-------------------------\n");
    for(int i = 1;i<=n;i++)
        printf("%d: v:%d l:%d r:%d d:%d\n",i,val[i],lc[i],rc[i],d[i]);
    printf("--------------------------\n");
}
}

namespace BCJ{
    int f[MAXN],r[MAXN];
    void init(int n){
        for(int i = 1;i<=n;i++)
            f[i] = i,r[i] = i;
    }
    int find(int x){
        return f[x] == x?x:f[x] = find(f[x]);
    }
    int un(int x,int y,int rr){
        int fx = find(x),fy = find(y);
        if(fx == fy) return false;
        f[fy] = fx;
        r[fx] = rr;
        return fx;
    }
    void print(int n){
        printf("-------------------------\n");
        for(int i = 1;i<=n;i++)
            printf("%d: f:%d r:%d\n",i,f[i],r[i]);
        printf("--------------------------\n");
    }
}
int n,m;
int num[MAXN];
int x[MAXN],y[MAXN];

int init(){
    if(scanf("%d",&n) != 1)
        return 0;
    for(int i = 1;i<=n;i++)
        scanf("%d",&num[i]);
    scanf("%d",&m);
    for(int i = 1;i<=m;i++)
        scanf("%d %d",&x[i],&y[i]);
    return 1;
}


void solve(){
    init(n,num);
    BCJ::init(n);
    for(int i = 1;i<=m;i++){
        int xx = x[i],yy = y[i];
        int fx = BCJ::find(xx),fy = BCJ::find(yy);
        if(fx==fy){printf("-1\n");continue;}
        fx = BCJ::r[fx],fy = BCJ::r[fy];
        int tx = del(fx),ty = del(fy);
        tx = merge(tx,ty);
        val[fx]/=2,val[fy]/=2;
        tx = merge(tx,fx),tx = merge(tx,fy);
        int rr = BCJ::un(fx,fy,tx);
        printf("%d\n",top(tx));
    }
    
}

void file(){
    freopen("test.txt","r",stdin);
}

int main(){
    //file();
    while(true){
        if(init())
            solve();
        else
            return 0;
    }
    return 0;
}