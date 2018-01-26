#include <cstdio>
#include <algorithm>
#define lson (nown<<1)
#define rson (nown<<1|1)
//#define max(x,y) ((x)^(((x)^(y))&-((x)<(y))))
using namespace std;

int tree[500000],n,m,t = 1;

void maintain(int nown){
    tree[nown] = max(tree[lson],tree[rson]);
}

void build(){
    while(t<=n) t<<=1;
    for(int i = 1;i<=n;i++)
        scanf("%d",&tree[t+i]);
    for(int i = t-1;i>=1;i--)
        maintain(i);
}

void update(int nown,int val){
    nown+=t;
    tree[nown] = val;
    for(nown>>=1;nown;nown>>=1)
        maintain(nown);
}

int query(int l,int r){
    int res = -0x3f3f3f3f;
    for(l=l+t-1,r=r+t+1;l^r^1;l>>=1,r>>=1){
        if(~l&1) res = max(res,tree[l^1]);
        if(r&1) res = max(res,tree[r^1]);
    }
    return res;
}


int main(){
    scanf("%d %d",&n,&m);
    build();
    getchar();
    for(int i = 1;i<=m;i++){
        char op = getchar();int a,b;
        if(op == 'Q'){
            scanf("%d %d",&a,&b);
            printf("%d\n",query(a,b));
        }
        else if(op == 'U'){
            scanf("%d %d",&a,&b);
            if(b>tree[t+a]){
                update(a,b);
            }
        }
        else{
            putchar('!');
        }
        getchar();
    }
    return 0;
}