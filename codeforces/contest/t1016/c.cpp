#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;

const int MAXN = 510000;

int n;
int a[MAXN][2];
int suma[MAXN],sumb[MAXN];
int bsuma[MAXN],bsumb[MAXN];
int rsuma[MAXN],rsumb[MAXN];

int cala(int pos){
    int t = pos;
    int ans = 0,nowt = 2*(pos-1);
    ans += (nowt-pos)*(suma[n]-suma[t-1]) + bsuma[n]-bsuma[pos-1];
    nowt += (n-pos+1),pos = 1;
    ans += (nowt-pos)*(sumb[n]-sumb[t-1]) + rsumb[t]-rsumb[n+1];
    return ans;
}

int calb(int pos){
    int t = pos;
    int ans = 0,nowt = 2*(pos-1);
    ans += (nowt-pos)*(sumb[n]-sumb[t-1])  + bsumb[n]-bsumb[pos-1];
    nowt += (n-pos+1),pos = 1;
    ans += (nowt-pos)*(suma[n]-suma[t-1])  + rsuma[t]-rsuma[n+1];
    return ans;
}

signed main(){
    scanf("%lld",&n);
    for(int i = 1;i<=n;i++){
        scanf("%lld",&a[i][0]);
    }
    for(int i = 1;i<=n;i++){
        scanf("%lld",&a[i][1]);
    }
    for(int i = 1;i<=n;i++){
        suma[i] = suma[i-1] + a[i][0];
        sumb[i] = sumb[i-1] + a[i][1];
    }
    for(int i = 1;i<=n;i++){
        bsuma[i] = bsuma[i-1] + i * a[i][0];
        bsumb[i] = bsumb[i-1] + i * a[i][1];
    }
    for(int i = 1;i<=n;i++){
        int t = n-i+1;
        rsuma[t] = rsuma[t+1] + i * a[t][0];
        rsumb[t] = rsumb[t+1] + i * a[t][1];
    }
    int ans = -1;
    int nowsum = 0,nowt = 0;
    for(int i = 1;i<=n;i++){
        int pos = !(i&1);
        if(pos == 0){
            ans = max(ans,nowsum+cala(i));
        }
        else{
            ans = max(ans,nowsum+calb(i));
        }
        nowsum += nowt * a[i][!(i&1)] + (nowt+1) * a[i][i&1] ;
        nowt += 2;
    }
    printf("%lld\n",max(ans,nowsum));
    return 0;
}