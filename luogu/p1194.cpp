#include <cstdio>
#include <algorithm>
using namespace std;

int f[600],n,c,cnt = 0,ans = 0;

struct Edge{
    int b,e,len;
}edge[30000];

int find(int x){
    return f[x] == x?x:f[x] = find(f[x]);
}

bool cmp(Edge a,Edge b){
    return a.len < b.len;
}

int main(){
    scanf("%d %d",&c,&n);
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=n;j++){
            int t;scanf("%d",&t);
            if(i >= j) continue;
            if(t == 0) continue;
            edge[cnt].b = i,edge[cnt].e = j,edge[cnt].len = t;
            cnt++;
        }
    }
    for(int i = 0;i<=n;i++)
        f[i] = i;
    for(int i = 1;i<=n;i++){
        edge[cnt].b = 0,edge[cnt].e = i,edge[cnt].len = c;
        cnt++;
    }
    int ans = 0;
    sort(edge,edge+cnt,cmp);
    for(int i = 0,ttt = 0;i<cnt;i++){
        int x1 = find(edge[i].b),x2 = find(edge[i].e);
        if(x1!=x2){
            ttt++;
            ans += edge[i].len;
            f[x1] = x2;
        }
        if(ttt == n)
            return printf("%d\n",ans),0;
    }
    return 0;
}