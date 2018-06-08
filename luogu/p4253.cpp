#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cctype>
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
ll dp[MAXN][logn][2];
ll dis[MAXN][logn];//从i节点向上j个节点的长度 
//点亮了i这个节点和子树的所有节点，下一个点亮到？级祖先的？儿子的最小代价 
//两种转移方式，左->右 or 右->左

#define p(i,j) (((1<<(j-1))<=i)?(i>>j):-1)
#define b(i,j) ((i>>(j-1))^1)
#define lson (i<<1)
#define rson ((i<<1)|1)

void init(){
    read(n);
    for(int i = 1;i<=n;i++)
        read(num[i]);
    dis[1][1] = 0;
    for(int i = 2;i<=n;i++){
        read(dis[i][1]);
        for(int j = 2;~p(i,j);j++)
            dis[i][j] = dis[p(i,1)][j-1] + dis[i][1];
    }
    // for(int i = 1;i<=n;i++){
    //     printf("%d:\n",i);
    //     for(int j = 1;~p(i,j);j++){
    //         printf("    %d:%lld\n",j,dis[i][j]);
    //     }
    // }
}

void solve(){
    //0 祖先 1 兄弟 
    for(int i = n;i >= 1;--i){
        for(int j = 1;~p(i,j);j++){
            dp[i][j][0] = dp[i][j][1] = 0x3f3f3f3f3f3f3f3f;
            if((i<<1) > n){//一个儿子都没有 
                dp[i][j][0] = dis[i][j] * num[p(i,j)];
                dp[i][j][1] = (dis[i][j] + dis[b(i,j)][1]) * num[b(i,j)];
            }
            else if(((i<<1)|1) > n){//只有左儿子 
                dp[i][j][0] = dp[lson][j+1][0] + dis[lson][1] * num[lson];
                dp[i][j][1] = dp[lson][j+1][1] + dis[lson][1] * num[lson];
            }
            else{//有两个儿子 
                dp[i][j][0] = min(dp[i][j][0],dp[lson][1][1]+dp[rson][j+1][0] + dis[lson][1] * num[lson]);
                dp[i][j][0] = min(dp[i][j][0],dp[rson][1][1]+dp[lson][j+1][0] + dis[rson][1] * num[rson]);
                dp[i][j][1] = min(dp[i][j][1],dp[lson][1][1]+dp[rson][j+1][1] + dis[lson][1] * num[lson]);
                dp[i][j][1] = min(dp[i][j][1],dp[rson][1][1]+dp[lson][j+1][1] + dis[rson][1] * num[rson]);
            }
        }
    }
    // for(int i = 1;i<=n;i++){
    //     printf("%d:\n",i);
    //     for(int j = 1;~p(i,j);j++){
    //         printf("    %d:0:%lld 1:%lld\n",j,dp[i][j][0],dp[i][j][1]);
    //     }
    // }
    ll ans = 0x3f3f3f3f3f3f3f3f;
    for(int s = 1;s<=n;s++){
        ll tmp = dp[s][1][0];
        // printf("s:%d\n",s);
        for(int i = p(s,1),last = s;~i;i = p(i,1),last = p(last,1)){
            // printf("    i:%d last:%d tmp:%lld\n",i,last,tmp);
            tmp += (b(last,1) <= n?
                  dis[b(last,1)][1] * num[b(last,1)] + dp[b(last,1)][2][0]:
                  dis[i][1] * num[p(i,1)]);
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