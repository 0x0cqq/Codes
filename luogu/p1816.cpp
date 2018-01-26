#include <cstdio>
#include <algorithm>
#define lson (nown<<1)
#define rson (nown<<1|1)
using namespace std;

int tree[1000000],n,m,t = 1;

void maintain(int nown){
    tree[nown] = min(tree[lson],tree[rson]);
}

void build(){
    while(t<=n) t<<=1;
    for(int i = 1;i<=n;i++)
        scanf("%d",&tree[t+i]);
    for(int i = t-1;i;i--)
        maintain(i);
}

int query(int l,int r){
    int res = 0x3f3f3f3f;
    for(l=l+t-1,r=r+t+1;l^r^1;l>>=1,r>>=1){
        if(~l&1) res = min(res,tree[l^1]);
        if(r&1) res = min(res,tree[r^1]);
    }
    return res;
}

int main(){
    scanf("%d %d",&n,&m);
    build();
    for(int i = 1;i<=m;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        printf("%d ",query(a,b));
    }
    return 0;
}