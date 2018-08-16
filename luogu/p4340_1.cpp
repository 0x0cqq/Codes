// luogu-judger-enable-o2
#include <cstdio>
using namespace std;
typedef long long ll;
#define mod 1000000007

const int MAXN = 110000;

ll pow(ll x,ll k){
    ll ans = 1;
    for(ll i = k;i;i>>=1,x = (x*x)%mod) if(i&1) ans = (ans * x)%mod;
    return ans;
}

ll niyuan(ll x){
    return pow(x,mod-2);
}


namespace SegTree{
ll sum[MAXN<<2],lazy[MAXN<<2];
#define lson (nown<<1)
#define rson (nown<<1|1)
#define mid ((l+r)>>1)
void push_up(int nown){
    sum[nown] = (sum[lson] + sum[rson])%mod;
}
void build(int nown,int l,int r,ll *num){
    lazy[nown] = 1;
    if(l == r){
        sum[nown] = num[l];
    }
    else{
        build(lson,l,mid,num);
        build(rson,mid+1,r,num);
        push_up(nown);
    }
}
void addlabel(int nown,ll v){
    (sum[nown] *= v)%=mod;
    (lazy[nown] *= v)%=mod;
}
void push_down(int nown){
    if(lazy[nown]){
        addlabel(lson,lazy[nown]),addlabel(rson,lazy[nown]);
        lazy[nown] = 1;
    }
}
void update(int nown,int l,int r,int ql,int qr,ll v){
    if(ql <= l && r <= qr){
        addlabel(nown,v); 
    }
    else{
        push_down(nown);
        if(ql <= mid)
            update(lson,l,mid,ql,qr,v);
        if(qr >= mid+1)
            update(rson,mid+1,r,ql,qr,v);
        push_up(nown);
    }
}
ll query(){
    return sum[1];
}
}

int n,m;
ll a[MAXN];
ll s[MAXN];
ll tmp[MAXN];

void init(){
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++)
        scanf("%lld",&a[i]);
}

void build(){
    s[1] = s[2] = 1;
    for(int i = 3;i<=n;i++)
        s[i] = (s[i-1] * 3)%mod;
    for(int i = 2;i<=n;i++)
        (s[i] *= 2)%=mod;
//	for(int i = 1;i<=n;i++){
//		printf("%lld ",s[i]);
//	}
//	printf("\n");
    tmp[n+1] = 1;
    for(int i = 1;i<=n;i++){
        int ttt = n-i+1;
        // printf("a:%lld\n",a[i]);
        tmp[ttt] = (tmp[ttt+1] * a[i])%mod;
    }
    for(int i = 1;i<=n;i++){
        (tmp[i] *= s[i]) %= mod;
        // printf("%lld ",tmp[i]);
    }
    //printf("\n");
    SegTree::build(1,1,n,tmp);
}

void solve(){
    ll pos,v;
    for(int i = 1;i<=m;i++){
        scanf("%lld %lld",&pos,&v);
        SegTree::update(1,1,n,1,n-pos+1,(niyuan(a[pos]) * v)%mod);
        a[pos] = v;
        printf("%lld\n",SegTree::query());
    }
}

int main(){
    init();
    build();
    solve();
    return 0;
}