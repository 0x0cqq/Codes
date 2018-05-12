#include <cstdio>
#include <algorithm>
#include <cctype>
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

const int MAXN = 220000;
int n,l,r;

namespace zkw{
    int dp[MAXN<<2],M;
    void init(int n){
        for(M = 1;M<=n+2;M<<=1);
    }
    void update(int pos,int x){
        pos+=M,dp[pos] = x;
        while(pos>>=1){
            dp[pos] = max(dp[pos<<1],dp[(pos<<1)|1]);
        }
    }
    int query(int l,int r){
        int ans = -0x3f3f3f3f;
        if(r == 0) return 0;
        if(l == 0) ans = 0,l = 1;
        for(l=l+M-1,r=r+M+1;l^r^1;l>>=1,r>>=1){
            if(~l&1) ans = max(ans,dp[l^1]);
            if(r&1) ans = max(ans,dp[r^1]);
        }
        return ans;
    }
}


int dd[MAXN],num[MAXN];

void init(){
    read(n),read(l),read(r);
    for(int i = 0;i<=n;i++){
        read(num[i]);
    }
    zkw::init(n);
}

void solve(){
    for(int i = 1;i<=n+r;i++){
        //printf("%d %d %d\n",i,max(0,i-r),min(i-l,n));
        if(i-l<0) dd[i] = -0x3f3f3f3f;
        else dd[i] = zkw::query(max(0,i-r),min(i-l,n))+num[i];
        zkw::update(i,dd[i]);
    }
    int ans = -0x3f3f3f3f;
    for(int i = n+1;i<=n+r;i++){
        //printf("%d:%d\n",i,dd[i]);
        ans = max(dd[i],ans);
    }
    printf("%d\n",ans);
}


int main(){
    init();
    solve();
    return 0;
}