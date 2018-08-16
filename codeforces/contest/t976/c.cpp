#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;

const int MAXN = 1000000;
 
struct query{
    int l,r,num;
}q[MAXN];

bool cmp(query a,query b){
    if(a.l!=b.l)
        return a.l < b.l;
    else
        return a.r > b.r;
}

int n;

main(){
    scanf("%lld",&n);
    for(int i = 1;i<=n;i++){
        scanf("%lld %lld",&q[i].l,&q[i].r);
        q[i].num = i;
    }
    sort(q+1,q+n+1,cmp);
    int maxn = -1,maxnum = -1;
    for(int i = 1;i<=n;i++){
        if(q[i].r <= maxnum){
            printf("%lld %lld\n",q[i].num,maxn);
            return 0;
        }
        if(q[i].r >= maxnum)
            maxn = q[i].num, maxnum = q[i].r;
    }
    printf("-1 -1\n");
    return 0;
}