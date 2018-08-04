#include <cstdio>
#include <algorithm>
using namespace std;
#define int long long
typedef long long ll;
const int MAXN = 110000;

int n;
struct land{
    ll x,y;
    bool operator <(const land &_a)const{
        if(x == _a.x)
            return y > _a.y;
        return x < _a.x;        
    }
}l[MAXN],b[MAXN];



ll dp[MAXN];
int tot;

double slope(int j,int k){
    return double(dp[j] - dp[k])/double(b[j+1].y - b[k+1].y);
}

void init(){
    scanf("%lld",&n);
    for(int i = 1;i<=n;i++)
        scanf("%lld %lld",&l[i].x,&l[i].y);
    sort(l+1,l+n+1);
    for(int i = n;i>=1;--i){
        if(l[i].y>b[tot].y) b[++tot] = l[i];
    }
    sort(b+1,b+tot+1);
    // for(int i = 1;i<=tot;i++){
    //     printf("x:%lld %lld %lld\n",i,l[i].x,l[i].y);
    // }
}

void solve(){
    static int q[MAXN],fi,la;//[fi,la]
    for(int i = 1;i<=tot;i++){
        while(fi < la && slope(q[fi],q[fi+1]) >= -b[i].x) fi++;
        dp[i] = dp[q[fi]] + 1LL * b[i].x * b[q[fi]+1].y;
        while(fi < la && slope(q[la],i) > slope(q[la-1],q[la])) --la;
        q[++la] = i;
    }
    printf("%lld\n",dp[tot]);
}

signed main(){
    init();
    solve();
    return 0;
}