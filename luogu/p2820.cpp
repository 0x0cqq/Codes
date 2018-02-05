#include <cstdio>
#include <algorithm>
using namespace std;

int n,m,f[101];

struct Edge{
    int b,e,len;
}edge[10010];

bool cmp(Edge a,Edge b){
    return a.len < b.len;
}

int find(int x){
    return f[x] == x?x:f[x] = find(f[x]);
}

int main(){
    scanf("%d %d",&n,&m);
    int l1 = 0,l2 = 0,cnt = 0;
    for(int i = 1;i<=m;i++){
        scanf("%d %d %d",&edge[i].b,&edge[i].e,&edge[i].len);
        l1 += edge[i].len;
    }
    sort(edge+1,edge+m+1,cmp);
    for(int i = 1;i<=n;i++)
        f[i] = i;
    for(int i = 1;i<=m;i++){
        int x1 = find(edge[i].b),x2 = find(edge[i].e);
        if(x1 == x2) continue;
        cnt++,f[x1] = x2;
        l2+=edge[i].len;
        if(cnt == n-1)
            break;
    }
    printf("%d\n",l1-l2);
    return 0;
}