// luogu-judger-enable-o2
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define pii pair<int,int>
#define ll long long

const int MAXN = 256;

int prime[8] = {2,3,5,7,11,13,17,19};

ll n,p;
ll f[MAXN][MAXN],g[2][MAXN][MAXN];
pii s[MAXN];


void init(){
    scanf("%lld %lld",&n,&p);
    for(int i = 2;i<=n;i++){
        int t = i;
        for(int j = 0;j<8;j++){
        while(t % prime[j] == 0){
                s[i].second |= (1<<j);
                t/=prime[j];
            }
        }
        s[i].first = t;
    }
    sort(s+2,s+n+1);
//	for(int i = 2;i<=n;i++){
//		printf("%d:%d %d\n",i,s[i].first,s[i].second);
//	}
}

void calc(){
    f[0][0] = 1;
    for(int i = 2;i<=n;i++){
        if(i==2||s[i].first==1||s[i].first != s[i-1].first){
            memcpy(g[0],f,sizeof(f)),memcpy(g[1],f,sizeof(f));
        }
        for(int j = MAXN-1;~j;--j){
            for(int k = MAXN-1;~k;--k){
                if((k & s[i].second) == 0)
                    (g[0][j|s[i].second][k] += g[0][j][k])%=p;
                if((j & s[i].second) == 0)
                    (g[1][j][k|s[i].second] += g[1][j][k])%=p;
            }
        }
        if(i==n || s[i].first==1||s[i].first != s[i+1].first){
            for(int j = 0;j<MAXN;j++){
                for(int k = 0;k<MAXN;k++){
                    if((j&k)==0)
                        f[j][k] = (g[0][j][k] + g[1][j][k] - f[j][k])%p;
                }
            }
        }
    }
}

void output(){
    ll ans = 0;
    for(int i = 0;i<MAXN;i++){
        for(int j = 0;j<MAXN;j++){
            if((i&j)==0) (ans += f[i][j])%=p;
        }
    }
    printf("%lld\n",(ans%p+p)%p);
}

int main(){
    init();
    calc();
    output();
    return 0;
}