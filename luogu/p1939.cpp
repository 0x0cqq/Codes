#include <cstdio>
#include <algorithm>
#include <cstring>
#define ll long long 
#define mod 1000000007
using namespace std;

struct Matrix{
    ll a[4][4];
    Matrix(){memset(a,0,sizeof(a));}
};

Matrix I;

Matrix mul(Matrix &_a,Matrix &_b){
    Matrix tmp;
    for(int i = 1;i<=3;i++){
        for(int j = 1;j<=3;j++){
            for(int k = 1;k<=3;k++){
                tmp.a[i][j] += _a.a[i][k] * _b.a[k][j];
            }
            tmp.a[i][j] %= mod;
        }
    }
    return tmp;
}

Matrix pow(Matrix x,int k){
    Matrix ans;
    for(int i = 1;i<=3;i++) ans.a[i][i] = 1;
    for(int i = k;i;i>>=1,x = mul(x,x)){
        if(i & 1) ans = mul(ans,x);
    }
    return ans;
}



void init(){
    I.a[1][2] = 1,I.a[2][3] = 1;
    I.a[3][1] = 1,I.a[3][3] = 1;
}


int getans(int k){
    Matrix tmp = pow(I,k-1);
    ll ans = 0;
    ans += tmp.a[1][1] + tmp.a[1][2] + tmp.a[1][3];
    ans %= mod;
    return int(ans);
}

int main(){
    init();
    int T,t;
    scanf("%d",&T);
    for(int i = 1;i<=T;i++){
        scanf("%d",&t);
        printf("%d\n",getans(t));
    }
    return 0;
}