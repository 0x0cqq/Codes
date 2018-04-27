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

const int MAXN = 110000;

struct Edge{
    int from,to;
    int len,nex;
}edge[MAXN<<1];

int n,m;
int fir[MAXN],ecnt = 1;
int num[MAXN];

void addedge(int a,int b,int c){
    edge[ecnt] = (Edge){a,b,c,fir[a]};
    fir[a] = ecnt++;
}

void init(){
    read(n);
    for(int i = 1;i<=n-1;i++){
        int a,b,c;
        read(a),read(b),read(c);
        addedge(a,b,c);
        addedge(b,a,c);
    }
}

void dfs(int nown,int f){
    for(int nowe = fir[nown];nowe;nowe = edge[nown].nex){
        int v = edge[nowe].to;
        if(v == f) continue;
        num[v] = num[nown] ^ edge[nowe].len;
        dfs(v,nown);
    }
}


void solve(){
    dfs(1,0);
    read(m);
    int a,b;
    for(int i = 1;i<=m;i++){
        read(a),read(b);
        print(num[a]^num[b]),print('\n');
    }
}

int main(){
    init();
    solve();
    flush();
    return 0;
}