#include <cstdio>
#include <algorithm>
using namespace std;

int n,m,f[1100];

struct Edge{
    int b,e,len;
}edge[11000];

inline bool cmp(Edge a,Edge b){return a.len<b.len;}
inline int find(int x){return f[x] == x? x:f[x] = find(f[x]);}

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 0;i<m;i++)
        scanf("%d %d %d",&edge[i].b,&edge[i].e,&edge[i].len);
    sort(edge,edge+m,cmp);
    for(int i = 1;i<=n;i++)
        f[i] = i;
    int cnt = 0;
    for(int i = 0;i<m;i++){
        int x1 = find(edge[i].b),x2 = find(edge[i].e);
        if(x1!=x2)
            cnt++,f[x1] = x2;
        if(cnt == n-1)
            return printf("%d\n",edge[i].len),0;
    }
}