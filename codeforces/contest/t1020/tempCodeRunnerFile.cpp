#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <set>
#define int  long long

using namespace std;

const int MAXN = 3100;

int num[MAXN];
int p[MAXN],c[MAXN];

multiset<int> S1,S2;

double rnd(){
    int a = rand()+1,b = rand()+1;
    a %= b;
    double t = double(a)/b - 1;
    return 1 + 0.1 * t;
}

int n,m;

signed main(){
    scanf("%lld %lld",&n,&m);
    for(int i = 1;i<=n;i++){
        scanf("%lld %lld",&p[i],&c[i]);
        num[p[i]]++;
    }
    long long ans = 0,nnn = 0;
    for(int i = 1;i<=n;i++){
        if(p[i] == 1){
            nnn++;
        }
    }
    for(int j = 1;j<=n;j++){
        int maxn = *max_element(num+2,num+m+1);
        int t = 1;
        for(int i = 2;i<=m;i++){
            if(num[i] == maxn)
                t++;
        }
        int nowmax = 0x3f3f3f3f3f3f3f3f,nown = -1;
        if(nnn > maxn) break;
        for(int i = 1;i<=n;i++){
            if(p[i] == 1) continue;
            if(num[p[i]] == maxn){
                if(nowmax >= c[i]){
                    nown = i,nowmax = c[nown];
                }
            }
            else{
                if(nowmax > c[i] * rnd()*double(t)/(t-1)){
                    nown = i,nowmax = c[nown] * rnd()*double(t)/(t-1);
                }
            }
        }
        nnn++;
        num[p[nown]]--;
        p[nown] = 1;
        ans += c[nown];
    }
    printf("%lld\n",ans);
    return 0;
}
