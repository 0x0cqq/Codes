#include <cstdio>
#include <cstring>
using namespace std;
#define mod 1000000007
const int MAXN = 4;typedef long long ll;
ll n,m = 2;

struct Matrix{
    ll a[MAXN][MAXN];
    Matrix(int op = 0){
        memset(a,0,sizeof(a));
        if(op){
            for(int i = 1;i<=m;i++)
                a[i][i] = 1;
        }
    }
};

Matrix mul(Matrix &_a,Matrix &_b){
    Matrix ans; 
    for(int i = 1;i<=m;i++){
        for(int j = 1;j<=m;j++){
            for(int k = 1;k<=m;k++){
                ans.a[i][j] += _a.a[i][k] * _b.a[k][j];
            }
            if(ans.a[i][j] >= mod) ans.a[i][j] %= mod;
        }
    }
    return ans;
}

Matrix pow(Matrix x,ll k){
    Matrix ans(1);
    for(ll i = k;i;i>>=1,x = mul(x,x)) if(i&1) ans = mul(ans,x);
    return ans;
}

void init(){
    scanf("%lld",&n);
}

void solve(){
    if(n <= 2){
        printf("1\n");
        return;
    }
    n -= 2;
    Matrix M;
    M.a[1][1] = M.a[1][2] = M.a[2][1] = 1;
    M = pow(M,n);
    ll ans = (M.a[1][1] + M.a[1][2]) % mod;
    printf("%lld\n",ans);
}

int main(){
    init();
    solve();
    return 0;
}