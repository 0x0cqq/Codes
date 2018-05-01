#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;

namespace fast_io {
    inline char read(){static const int IN_LEN=1000000;static char buf[IN_LEN],*s,*t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++):*s++;}
    inline void read(int &x){static bool f;static char c;for(f=false,c=read();!isdigit(c);c=read()){if(c=='-')f=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(f)x=-x;}
    inline void read(char *a){static char c=read();while(c!=-1&&(c==' '||c=='\n'||c=='\r'))c=read();while(c!=-1&&c!='\r'&&c!=' '&&c!='\n')*a++=c,c=read();*a=0;}
    const int OUT_LEN=1000000;char obuf[OUT_LEN],*ooh=obuf;
    inline void print(char c){if(ooh==obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;*ooh++=c;}
    inline void print(int x){static int buf[30],cnt;if(x==0)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while(cnt)print((char)buf[cnt--]);}}
    inline void print(char *a){while(*a)print(*a++);}
    inline void flush(){fwrite(obuf,1,ooh-obuf,stdout);}
}using namespace fast_io;

const int MAXN = 2100;

int n,m,num[MAXN][MAXN],ans1,ans2;

void init(){
    read(n),read(m);//read();
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            num[i][j] = read()^48;
            num[i][j] ^= ((i+j) & 1);
            read();
        }
        //read();
    }
}

void solve(){
    static int l[MAXN][MAXN],r[MAXN][MAXN],h[MAXN][MAXN];
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++)
            l[i][j] = num[i][j] == num[i][j-1]? l[i][j-1] + 1:1;
        for(int j = m;j>=1;--j)
            r[i][j] = num[i][j] == num[i][j+1]? r[i][j+1] + 1:1; 
    }
    for(int i = 2;i<=n;i++){
        for(int j = 1;j<=m;j++){
            if(num[i][j] == num[i-1][j]){
                h[i][j] += h[i-1][j]+1;
                l[i][j] = min(l[i][j],l[i-1][j]);
                r[i][j] = min(r[i][j],r[i-1][j]);
            }
        }
    }
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            int s = min(h[i][j]+1,l[i][j]+r[i][j] - 1);
            ans1 = max(ans1,s*s);
            ans2 = max(ans2,(h[i][j]+1)*(l[i][j] + r[i][j] - 1));
        }
    }
    print(ans1),print('\n'),print(ans2),print('\n');
}

int main(){
    init();
    solve();
    flush();
    return 0;
}