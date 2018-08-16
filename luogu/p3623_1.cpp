#include <cstdio>
#include <algorithm>
#include <cstring>
#define nosolution() printf("no solution\n");return;  
using namespace std;

const int MAXN = 110000;

int n,m,k;
struct Edge{
    int from,to,len;
}edge[MAXN];

bool cmp(Edge a,Edge b){
    return a.len < b.len;
}

int f[MAXN];
void init(int n){
    for(int i = 1;i<=n;i++) f[i] = i;
}
int find(int x){
    return f[x] == x?x:f[x] = find(f[x]);
}

void solve(){
    static Edge ans[MAXN];
    int tot = 0;
    init(n);sort(edge+1,edge+m+1,cmp);
    for(int i = 1;i<=m;i++){
        Edge &e = edge[i];
        int fx = find(e.from),fy = find(e.to);
        if(fx != fy){
            f[fx] = fy;
            if(e.len == 1){
                tot++;
                ans[tot] = e;
            }
        }
        if(e.len == 1){
            e.len = -1;
        }	
    }
    init(n);sort(edge+1,edge+m+1,cmp);
    if(tot > k){nosolution();}
    for(int i = 1;i<=tot;i++){
        int fx = find(ans[i].from),fy = find(ans[i].to);
        f[fx] = fy;
    }
    for(int i = 1;i<=m;i++){
        Edge &e = edge[i];
        if(tot == n-1) break;
        int fx = find(e.from),fy = find(e.to);
        if(tot == k && e.len == -1) continue;
        if(tot < k && e.len != -1){nosolution();}
        if(fx != fy){
            f[fx] = fy;
            ans[++tot] = e;
        }
    }	
    if(tot!=n-1){nosolution();}
    for(int i = 1;i<=n-1;i++)
        printf("%d %d %d\n",ans[i].from,ans[i].to,abs(ans[i].len)^1);
}

void init(){
    scanf("%d %d %d",&n,&m,&k);
    for(int i = 1;i<=m;i++){
        scanf("%d %d %d",&edge[i].from,&edge[i].to,&edge[i].len);
        edge[i].len^=1;
    }
}

int main(){
    init();
    solve();
    return 0;
}