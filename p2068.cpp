#include <cstdio>
#include <algorithm>
#define lson (nown<<1)
#define rson (nown<<1|1)
using namespace std;

int tree[1000000],n,m,t = 1;

void maintain(int nown){
    tree[nown] = tree[lson]+tree[rson];
}

void build(){
    while(t<=n) t<<=1;
}

void update(int nown,int val){
    tree[nown+=t]+=val;
    while((nown>>=1)>=1)
        maintain(nown);
}

int query(int l,int r){
    int res = 0;
    for(l=l+t-1,r=r+t+1;l^r^1;l>>=1,r>>=1){
        if(~l&1) res += tree[l^1];
        if( r&1) res += tree[r^1];
    }
    return res;
}

int main(){
    scanf("%d %d",&n,&m);
    getchar();getchar();
    build();
    for(int i = 1;i<=m;i++){
        char op = getchar();
        int a,b;
        scanf("%d %d",&a,&b);
        if(op == 'x')
            update(a,b);
        else if(op == 'y')
            printf("%d\n",query(a,b));
        getchar();getchar();
    }
    return 0;
}