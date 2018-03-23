#include <cstdio>
#include <cctype>
#include <vector>
using namespace std;

namespace fast_io {
    inline char read() {static const int IN_LEN = 1000000;static char buf[IN_LEN], *s, *t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++) : *s++;}
    inline void read(int &x) {static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-') iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!= -1&&(c==' '||c =='\n'))c=read();while(c!=-1&&c!=' '&&c!='\n') *a++ = c,c = read();*a = 0;}
    const int OUT_LEN=1000000;char obuf[OUT_LEN],*ooh=obuf;
    inline void print(char c){if(ooh==obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;*ooh++ = c;}
    inline void print(int x) {static int buf[30], cnt;if (x == 0)print('0');else{if(x<0) print('-'),x=-x;for(cnt=0;x;x/=10) buf[++cnt] = x%10+48;while (cnt) print((char)buf[cnt--]);}}
    inline void print(char *a){while(*a) print(*a++);}
    inline void flush(){fwrite(obuf,1,ooh-obuf,stdout);}
}using namespace fast_io;

const int MAXN = 110000;

vector<int> edge[MAXN];

int n,m,low[MAXN],dfn[MAXN],vis[MAXN],cnt = 1,ans = 0;
int cut[MAXN];

void dfs(int nown,int fa){
    vis[nown] = 1;
    dfn[nown] = low[nown] = cnt++;
    int child = 0;
    for(int i = 0;i<edge[nown].size();i++){
        int to = edge[nown][i];
        if(to!=fa&&vis[to] == 1)
            low[nown] = min(low[nown],dfn[to]);
        if(vis[to] == 0){
            dfs(to,nown),low[nown] = min(low[nown],low[to]);
            child++;
            if((fa==-1&&child>1)||(fa!=-1&&dfn[nown]<=low[to]))
                if(!cut[nown])ans++,cut[nown] = 1;
        }
    }
    vis[nown] = 2;
}

void init(){
    read(n),read(m);
    int a,b;
    for(int i = 1;i<=m;i++){
        read(a),read(b);
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
}

void solve(){
    for(int i = 1;i<=n;i++){
        if(vis[i] == 0)
            dfs(i,-1);
    }
    print(ans),print('\n');
    for(int i = 1;i<=n;i++){
        if(cut[i] == 1)
            print(i),print(' ');
    }
}

int main(){
    init();
    solve();
    flush();
    return 0;
}