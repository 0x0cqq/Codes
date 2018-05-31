#include <cstdio>
#include <queue>
#include <algorithm>
#include <cctype>
using namespace std;

const int MAXN = 110000,logn = 20;

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

int n,s[MAXN];
vector<int> edge[MAXN],edge1[MAXN];

void init(){
    read(n);
    int a = -1;
    for(int i = 1;i<=n;i++){
        read(a);
        while(a!=0){
            edge[i].push_back(a);
            read(a);
        }
    }
}

int in[MAXN],sheng[MAXN];

int topo[MAXN],siz[MAXN];
int f[MAXN][logn],dep[MAXN],rt;

int lca(int x,int y){
    if(x == -1) return y;
    if(y == -1) return x;
    if(dep[x] < dep[y]) swap(x,y);
    for(int j = logn-1;j>=0;j--)
        if(dep[f[x][j]] >= dep[y])
            x = f[x][j];
    if(x==y) return x;
    for(int j = logn-1;j>=0;j--)
        if(f[x][j] != f[y][j])
            x=f[x][j],y = f[y][j];
    return f[x][0];
}

void build(){
    queue<int> q;int cnt = 0;
    for(int i = 1;i<=n;i++)
        for(int j = 0;j<edge[i].size();j++)
            in[edge[i][j]]++;
    for(int i = 1;i<=n;i++)
        if(in[i] == 0)
            q.push(i);
    
    while(!q.empty()){
        int nown = q.front();q.pop();
        topo[++cnt] = nown;
        for(int i = 0;i<edge[nown].size();i++){
            int v = edge[nown][i];
            if(--in[v] == 0) q.push(v);
        }
    }
    reverse(topo+1,topo+n+1);
    //for(int i = 1;i<=n;i++){
    //	printf("%d ",topo[i]);
    //}
    //printf("\n");
}

void solve(){
    rt = n+1;
    dep[rt] = 1;
    for(int i = 1;i<=n;i++){
        if(edge[i].size() == 0)
            f[i][0] = rt,dep[i] = 2;
    }
    for(int i = 1;i<=n;i++){
        int nown = topo[i];
        if(dep[nown]!=0) continue;
        int tmp = -1;
        for(int j = 0;j<edge[nown].size();j++){
            int v = edge[nown][j];
            //printf("%d\n",v);
            tmp = lca(v,tmp);
        }
        //printf("%d:%d\n",nown,tmp);
        f[nown][0] = tmp,dep[nown] = dep[tmp]+1;
        for(int j = 1;j<logn;j++)
            f[nown][j] = f[f[nown][j-1]][j-1];
    }
    for(int i = n;i>=1;--i){
        int nown = topo[i];
        siz[nown] += 1;
        siz[f[nown][0]] += siz[nown];
    }
    for(int i = 1;i<=n;i++){
        print(siz[i]-1),print('\n');
    }
}

int main(){
    init();
    build();
    solve();
    flush();
    return 0;
}