#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
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

const int MAXN = 110000,MAXM = 2100000;

struct stack{
    int num[MAXN],topnum;
    stack(){topnum = 0;}
    void pop(){topnum--;}
    int top(){return num[topnum-1];}
    void push(int val){num[topnum++] = val;}
    bool empty(){return topnum != 0;}
}a;

int n,m,ecnt = 1,X;

int fir[MAXN];
int cnt = 1,cnum = 0;
int low[MAXN],dfn[MAXN],siz[MAXN];
int col[MAXN];
int instack[MAXN];

struct Edge{
    int from,to,nex;
    bool operator < (Edge a)const{
        if(from == a.from)
            return to < a.to;
        return from < a.from;
    }
}edge[MAXM];

void addedge(int a,int b){
    edge[ecnt].from = a,edge[ecnt].to = b;
    edge[ecnt].nex = fir[a];fir[a] = ecnt++;
}

void dfs(int nown){
    low[nown] = dfn[nown] = cnt++;
    instack[nown] = 1;a.push(nown);
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to;
        if(dfn[v] == 0)
            dfs(v),low[nown] = min(low[v],low[nown]);
        else if(instack[v] == 1)
            low[nown] = min(dfn[v],low[nown]);
    }
    if(low[nown] == dfn[nown]){
        cnum++;int j = -1;
        do{
            j = a.top();a.pop();
            instack[j] = 0;
            col[j] = cnum;
            siz[cnum]++;
        }while(j!=nown);
    }
}

void tarjan(){
    for(int i = 1;i<=n;i++)
        if(dfn[i] == 0)
            dfs(i);
    for(int i = 1;i<=m;i++){
        edge[i].from = col[edge[i].from];
        edge[i].to = col[edge[i].to];
    }
    memset(fir,0,sizeof(fir));
    sort(edge+1,edge+m+1);
    int lastu = 0,lastv = 0;
    for(int i = 1;i<=m;i++){
        int u = edge[i].from,v = edge[i].to;
        if(u!=v&&(!(u==lastu&&v==lastv)))
            addedge(u,v);
        lastu = u,lastv = v;
    }
}

int dp[MAXN],num[MAXN];

void dfs2(int nown){
    dp[nown] = siz[nown],num[nown] = 1;
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to;
        if(dp[v] == 0) dfs2(v);
        if(dp[nown] < dp[v] + siz[nown])
            dp[nown] = dp[v] + siz[nown],num[nown] = num[v];
        else if(dp[nown] == dp[v] + siz[nown])
            num[nown] += num[v], num[nown] %= X;
    }
}

void solve(){
    for(int i = 1;i<=cnum;i++)
        if(num[i] == 0)
            dfs2(i);
    int ans1 = 0,ans2 = 0;
    for(int i = 1;i<=cnum;i++){
        if(dp[i] > ans1) ans1 = dp[i],ans2 = num[i];
        else if(dp[i] == ans1) ans2 += num[i],ans2 %=X;
    }
    print(ans1),print('\n'),print(ans2),print('\n');
}

void init(){
    read(n),read(m),read(X);
    int a,b;
    for(int i = 1;i<=m;i++){
        read(a),read(b);
        addedge(a,b);
    }
}

int main(){
    init();
    tarjan();
    solve();
    flush();
    return 0;
}