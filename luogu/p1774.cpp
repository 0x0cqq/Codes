#include <cstdio>
#include <algorithm>
#define ll long long
#define lowbit(x) ((x)&(-(x)))
using namespace std;


ll tree[1001000],n;

struct a{
    ll id,num;
}w[510000];

bool cmp1(a x,a y){
    return x.id<y.id;
}

bool cmp2(a x,a y){
    return x.num<y.num;
}

void insert(int x){
    while(x<=n){
        tree[x]++;
        x+=lowbit(x);
    }
}

ll query(int x){
    ll res = 0;
    while(x>0){
        res += tree[x];
        x-=lowbit(x);
    }
    return res;
}

int main(){
    scanf("%lld",&n);
    for(int i = 0;i<n;i++){
        scanf("%lld",&w[i].num);
        w[i].id = i;
    }
    sort(w,w+n,cmp2);
    ll last = w[0].num,nown = n;
    w[0].num = n;
    for(int i = 1;i<n;i++){
        if(w[i].num!=last){
            last = w[i].num;
            nown--;
        }
        w[i].num = nown;
    }
    sort(w,w+n,cmp1);
    ll ans = 0;
    for(int i = 0;i<n;i++){
        ans+=query(w[i].num-1);
        insert(w[i].num);
    }
    printf("%lld\n",ans);
    return 0;
}