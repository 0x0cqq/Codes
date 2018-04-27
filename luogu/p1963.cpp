#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 30000,MAXM = 100000;

struct Edge{
    int from,to;
    int nex;
}edge[MAXM];

int fir[MAXN],ecnt = 1;

int n;
int pre[MAXN],vis[MAXN];

void addedge(int a,int b){
    edge[ecnt] = (Edge){a,b,fir[a]};
    fir[a] = ecnt++;
}

bool dfs(int nown){
    if(vis[nown])
        return false;
    vis[nown] = 1;
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to;
        if(!pre[v] || dfs(pre[v])){
            pre[v] = nown;
            return true;
        }
    }
    return false;
}

void init(){
    scanf("%d",&n);
    int tmp;
    for(int i = 0;i < n;i++){
        scanf("%d",&tmp);
        addedge(i,max( (i-tmp+n)%n,(i+tmp+n)%n )+n);
        addedge(i,min( (i-tmp+n)%n,(i+tmp+n)%n )+n);
    }
}

bool solve(){
    for(int i = n-1;i >= 0;i--){
        memset(vis,0,sizeof(vis));
        if(dfs(i)) continue;
        else return false; 
    }
    return true;
}

void output(){
    static int ans[MAXN];
    for(int i = 0;i < n;i++){
        ans[pre[i+n]] = i;
    }
    for(int i = 0;i < n;i++){
        printf("%d ",ans[i]);
    }
    putchar('\n');
}

int main(){
    init();
    if(solve())
        output();
    else
        printf("No Answer\n");
    return 0;
}