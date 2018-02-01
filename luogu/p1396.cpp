#include <cstdio>
#include <algorithm>
using namespace std;

int f[11000],n,m,s,t;

struct Edge{
    int b,e,l;
}edge[30000];

inline bool cmp(Edge a,Edge b){return a.l<b.l;}
inline int find(int x){return f[x]==x? x :f[x] = find(f[x]);}

int main(){
    scanf("%d %d %d %d",&n,&m,&s,&t);
    for(register int i = 1;i<n;i++)
        f[i] = i;
    for(register int i = 0;i<m;i++)
        scanf("%d %d %d",&edge[i].b,&edge[i].e,&edge[i].l);
    sort(edge,edge+m,cmp);
    for(register int i = 0;i<m;i++){
        int x = find(edge[i].b),y =find(edge[i].e);
        if(x!=y)
            f[x] = y;
        if(find(s)==find(t)){
            printf("%d\n",edge[i].l);return 0;
        }
    }
    printf("%d\n",-1);
    return 0;
}