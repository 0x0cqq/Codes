#include <cstdio>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;

namespace fast_io {
    inline char read(){static const int IN_LEN=1000000;static char buf[IN_LEN],*s,*t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++) : *s++;}
    inline void read(int &x){static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-')iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!=-1&&(c==' '||c=='\n'||c=='\r'))c=read();while(c!=-1&&c!='\r'&&c!=' '&&c!='\n') *a++=c,c=read();*a=0;}
    const int OUT_LEN=1000000;char obuf[OUT_LEN],*ooh=obuf;
    inline void print(char c){if(ooh==obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;*ooh++ = c;}
    inline void print(int x){static int buf[30],cnt;if(x==0)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while (cnt) print((char)buf[cnt--]);}}
    inline void print(char *a){while(*a) print(*a++);}
    inline void flush(){fwrite(obuf,1,ooh-obuf,stdout);}
}using namespace fast_io;

const int MAXN = 3100;

int n,m,num[MAXN];
int dp[MAXN][MAXN],siz[MAXN];
//dp[i][j] -> 以i为根的子树里面选j个叶子的最大收益

struct Edge{
    int to,len;
};

vector<Edge> edge[MAXN];

void init(){
    read(n),read(m);
    int k,a,c;
    for(int i = 1;i<=n-m;i++){
        read(k);
        for(int j = 1;j<=k;j++){
            read(a),read(c);
            edge[i].push_back((Edge){a,c});
        }
    }
    for(int i = n-m+1;i<=n;i++)
        read(num[i]);
}

void dfs1(int x){
    if(x >= n-m+1) 
        siz[x] = 1;
    for(int i = 0;i<edge[x].size();i++){
        int v = edge[x][i].to;
        dfs1(v);
        siz[x] += siz[v];
    }
}

void dfs2(int x){
    dp[x][0] = 0,dp[x][1] = x >= n-m+1?num[x]:-0x3f3f3f3f;
    int sum = 0;
    for(int i = 0;i<edge[x].size();i++){
        int v = edge[x][i].to,l = edge[x][i].len;
        dfs2(v);
        sum += siz[v];
        //printf("v:%d siz:%d\n",v,siz[v]);
        for(int j = min(sum,m);j>=1;--j){
            for(int k = 1;k<=siz[v];k++){
                if(j-k>=0)
                    dp[x][j] = max(dp[x][j],dp[x][j-k] + dp[v][k] - l);
                else
                    break;
                //printf("    x:%d j:%d dp[%d][%d]:%d\n",x,j,x,j,dp[x][j]);
            }
        }
    }
}

void solve(){
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            dp[i][j] = -0x3f3f3f3f;
        }
    }
    dfs1(1);
    dfs2(1);
    for(int j = m;j>=0;j--){
        if(dp[1][j] >= 0){
            print(j);break;
        }
    }
}

int main(){
    init();
    solve();
    return 0;
}