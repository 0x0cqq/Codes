#include <cstdio>
#include <algorithm>
using namespace std;

int n,m,p[10000];
long long ans = 0;

struct edge{
    int i,j,l;
    void b(int q,int w,int e){
        i = q;j = w;l = e;
    }
}k[201000];


inline bool check(){
    for(int i = 1;i<=n;i++){
        if(p[i] == 0)
            return false;
    }
    return true;
}

inline int find(int x){
    return (p[x] == x?x:p[x] = find(p[x]));
}

inline bool cmp(edge a,edge b){
    return a.l<b.l;
}

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 0;i<m;i++){
        int a,b,x;
        scanf("%d %d %d",&a,&b,&x);
        k[i].b(a,b,x);
    }
    sort(k,k+m,cmp);
    for(int i = 1;i<=n;i++)
        p[i] = i;
    int num = 0;
    for(int w = 0;w<m;w++){
        int x = find(k[w].i),y = find(k[w].j);
        //printf("%d %d %d %d\n",k[w].i,k[w].j,x,y);
        if(x != y){
            p[x] = y;
            ans+=k[w].l;
            num++;
            if(num == n-1){
                printf("%lld\n",ans);
                return 0;
            }
        }
    }
    printf("orz\n");
    return 0;
}