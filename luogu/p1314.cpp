#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define ll long long
using namespace std;

ll n,m,s,l[201000],r[201000],w[201000],v[201000],q1[201000],q2[201000];

inline void qr(ll &x){
    x = 0;char ch = getchar();
    while(ch<'0'||ch>'9'){
        ch = getchar();
    }
    while(ch>='0'&&ch<='9'){
        x = (x<<3)+(x<<1)+ch-48;
        ch = getchar();
    }
}

ll cal(ll nown){
    q1[0] = q2[0] = 0;
    for(int i = 1;i<=n;i++){
        q1[i] = q1[i-1],q2[i] = q2[i-1];
        if(w[i]>=nown)
            q1[i]++,q2[i]+=v[i];
    }
    ll ans = 0;
    for(int i = 0;i<m;i++)
        ans+=(q1[r[i]]-q1[l[i]-1])*(q2[r[i]]-q2[l[i]-1]);
    return ans;
}


int main(){
    qr(n),qr(m),qr(s);
    for(int i = 1;i<=n;i++)
        qr(w[i]),qr(v[i]);
    for(int i = 0;i<m;i++)
        qr(l[i]),qr(r[i]);
    ll b = 0,e = 1e6;
    while(e!=b){
        ll mid = (b+e)>>1;
        ll mid_cal = cal(mid);
        if(mid_cal<s) e = mid;
        else          b = mid+1;
    }
    ll yyy = abs(cal(b)-s),xxx =abs(cal(b-1)-s);
    ll ans = yyy<xxx?yyy:xxx;
    printf("%lld\n",ans);
    return 0;
}


