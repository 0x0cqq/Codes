#include <cstring>
#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;
#define ll long long

const int SIZE = 1024*1024;char ibuf[SIZE],*s,*t;

inline char read(){
    if(s==t) t=(s=ibuf)+fread(ibuf,1,SIZE,stdin);
    return s==t?-1:*s++;
}

template <typename T>
inline void read(T &x){
    static char c;bool iosig;
    for(c=read(),iosig=0;!isdigit(c);c=read()){
        if(c==-1) return;
        iosig |= (c=='-');
    }
    for(x=0;isdigit(c);c=read())
        x = (((x<<2)+x)<<1) + (c^48);
    if(iosig) x = -x;
}

const int MAXN = 210000,logn = 20;

int n;
ll num[MAXN]; 
ll dp[2][logn][MAXN];
ll dis[logn][MAXN];//从i节点向上j个节点的长度 
//点亮了i这个节点和子树的所有节点，下一个点亮到？级祖先的？儿子的最小代价 
//两种转移方式，左->右 or 右->左

#define p(i,j) (((1<<(j-1))<=i)?(i>>j):-1)
#define b(i,j) ((i>>(j-1))^1)
#define lson (i<<1)
#define rson ((i<<1)|1)

void init(){
    read(n);
    for( int i = 1;i<=n;i++)
        read(num[i]);
    dis[1][1] = 0;
    for( int i = 2;i<=n;i++){
        read(dis[1][i]);
        for( int j = 2;~p(i,j);j++)
            dis[j][i] = dis[j-1][p(i,1)] + dis[1][i];
    }
}

void solve(){
    //0 祖先 1 兄弟 
    for( int i = n;i >= 1;--i){
        for( int j = 1;~p(i,j);j++){
            dp[0][j][i] = dp[1][j][i] = 0x3f3f3f3f3f3f3f3f;
            if((i<<1) > n){//一个儿子都没有 
                dp[0][j][i] = dis[j][i] * num[p(i,j)];
                dp[1][j][i] = (dis[j][i] + dis[1][b(i,j)]) * num[b(i,j)];
            }
            else if(((i<<1)|1) > n){//只有左儿子 
                dp[0][j][i] = dp[0][j+1][lson] + dis[1][lson] * num[lson];
                dp[1][j][i] = dp[1][j+1][lson] + dis[1][lson] * num[lson];
            }
            else{//有两个儿子 
                dp[0][j][i] = min(dp[0][j][i],dp[1][1][lson]+dp[0][j+1][rson] + dis[1][lson] * num[lson]);
                dp[0][j][i] = min(dp[0][j][i],dp[1][1][rson]+dp[0][j+1][lson] + dis[1][rson] * num[rson]);
                dp[1][j][i] = min(dp[1][j][i],dp[1][1][lson]+dp[1][j+1][rson] + dis[1][lson] * num[lson]);
                dp[1][j][i] = min(dp[1][j][i],dp[1][1][rson]+dp[1][j+1][lson] + dis[1][rson] * num[rson]);
            }
        }
    }
    ll ans = 0x3f3f3f3f3f3f3f3f;
    for( int s = 1;s<=n;s++){
        ll tmp = dp[0][1][s];
        for( int i = p(s,1),last = s;~i;i = p(i,1),last = p(last,1)){
            tmp += (b(last,1) <= n?
                  dis[1][b(last,1)] * num[b(last,1)] + dp[0][2][b(last,1)]:
                  dis[1][i] * num[p(i,1)]);
        }
        ans = min(ans,tmp);
    }
    printf("%lld\n",ans);
}

int main(){
    init();
    solve();
    return 0;
}