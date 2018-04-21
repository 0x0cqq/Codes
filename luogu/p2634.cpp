#include <cstdio>
#include <cctype>
#include <algorithm>
#define ll long long
using namespace std;

namespace fast_io {
    inline char read(){static const int IN_LEN=1000000;static char buf[IN_LEN],*s,*t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++) : *s++;}
    inline void read(int &x){static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-')iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
}using namespace fast_io;

ll gcd(ll a,ll b){// a < b;
    return a == 0?b:gcd(b%a,a);
}

const int MAXN = 110000;

struct Edge{
    int from,to;
    int len,nex;
}edge[MAXN];int ecnt = 2;
int fir[MAXN];
void addedge(int a,int b,int l){
    edge[ecnt] = (Edge){a,b,l,fir[a]};
    fir[a] = ecnt++;
    edge[ecnt] = (Edge){b,a,l,fir[b]};
    fir[b] = ecnt++;
}

//-----
int n,m;
int f[MAXN],siz[MAXN],vis[MAXN];
int rt,sz;
int num[3],tmp[3];
ll ans = 0;

//-----
void getroot(int nown,int fa){
    siz[nown] = 1,f[nown] = 0;
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to;
        if(vis[v] || v == fa) continue;
        getroot(v,nown);
        siz[nown] += siz[v];
        f[nown] = max(f[nown],siz[v]); 
    }
    f[nown] = max(f[nown],sz - siz[nown]);
    if(f[nown] < f[rt]) rt = nown;
}

void getdeep(int nown,int fa,int d){
    //printf("nown:%d d:%d\n",nown,d);
    num[d]++;
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to,l = edge[nowe].len;
        if(vis[v] || v == fa) continue;
        getdeep(v,nown,(d+l)%3);
    }
}

void work(int nown){
    tmp[0] = 1;tmp[1] = tmp[2] = 0;
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to,l = edge[nowe].len;
        if(vis[v]) continue;
        num[0] = num[1] = num[2] = 0;
        getdeep(v,nown,l);
        ans -= num[0]*num[0] + 2*num[1]*num[2];
        tmp[0] += num[0],tmp[1]+=num[1],tmp[2]+=num[2];
    }
    ans += tmp[0] * tmp[0] + 2*tmp[1] * tmp[2];
}

void solve(int nown){
    //printf("solve:%d\n",nown);
    vis[nown] = 1;
    work(nown);
    //printf("%d: 0:%d 1:%d 2:%d\n",nown,tmp[0],tmp[1],tmp[2]);
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to;
        if(vis[v]) continue;
        f[rt = 0] = sz = siz[v];
        getroot(v,rt);
        solve(rt);
    }
}

void init(){
    read(n);
    int a,b,c;
    for(int i = 1;i<=n-1;i++){
        read(a),read(b),read(c);
        addedge(a,b,c%3);
    }
}

void solve(){
    f[rt = 0] = sz = n;
    getroot(1,rt);
    solve(rt);
    ll ans2 = n*n;
    //printf("%lld %lld %lld\n",ans,ans2,gcd(ans,ans2));
    printf("%lld/%lld\n",ans/gcd(ans,ans2),ans2/gcd(ans,ans2));
}

int main(){
    init();
    solve();
    return 0;
}