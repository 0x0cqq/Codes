#include <cstdio>
#include <algorithm>
using namespace std;

int f[3000],n,m,k;

struct Edge{
    int b,e,len;
}edge[20000];

bool cmp(Edge a,Edge b){
    return a.len < b.len;
}

int find(int x){
    return f[x] == x?x:f[x] = find(f[x]);
}

int main(){
    scanf("%d %d %d",&n,&m,&k);
    for(int i = 0;i<m;i++)
        scanf("%d %d %d",&edge[i].b,&edge[i].e,&edge[i].len);
    sort(edge,edge+m,cmp);
    for(int i = 1;i<=n;i++)
        f[i] = i;
    int cnt = n,ans = 0;
    for(int i = 0;i<=m;i++){
        if(cnt <= k){
            printf("%d\n",ans);
            return 0;
        }
        if(i == m) break;
        int x1 = find(edge[i].b),x2 = find(edge[i].e);
        if(x1!=x2)
            cnt--,ans+=edge[i].len,f[x1] = x2;
    }
    printf("No solution\n");    
    return 0;
}