#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <vector>
using namespace std;
#define ll long long

const int MAXN = 2100;

namespace fast_io {
    inline char read(){static const int IN_LEN=1000000;static char buf[IN_LEN],*s,*t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++) : *s++;}
    inline void read(int &x){static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-')iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
}using namespace fast_io;

struct Edge{
    int to,len;
};

int n,k;
ll dp[MAXN][MAXN];
int siz[MAXN];
vector<Edge> edge[MAXN];

void init(){
    read(n),read(k);
    int a,b,c;
    for(int i = 1;i<=n-1;i++){
        read(a),read(b),read(c);
        edge[a].push_back((Edge){b,c});
        edge[b].push_back((Edge){a,c});
    }
}

void dfs(int x,int fa){
    siz[x] = 1;dp[x][0] = dp[x][1] = 0;
    for(int i = 0;i<edge[x].size();i++){
        int v = edge[x][i].to;
        if(v == fa) continue;
        dfs(v,x);
        // printf("v:%d siz:%d %d\n",v,siz[v],siz[x]);
        for(int j = min(siz[x],k);j>=0;--j){
            for(int w = siz[v];w>=0;--w){
                if(j+w<=k)
                    dp[x][j+w] = max(dp[x][j+w],dp[x][j] + dp[v][w] + 1LL * (1LL * w*(k-w) + 1LL*(siz[v]-w)*(n-k-siz[v]+w))*1LL*edge[x][i].len);  
            }
            // printf("x:%d j:%d dp[%d][%d]:%lld\n",x,j,x,j,dp[x][j]);
        }
        siz[x] += siz[v];
    }
}

void solve(){
    // for(int i = 0;i<=n;i++)
    //     for(int j = 0;j<=k;j++)
    //         dp[i][j] = -0x3f3f3f3f3f3f3f;
    dfs(1,0);
    printf("%lld\n",dp[1][k]);
}

signed main(){
    init();
    solve();
    return 0;
}