#include <cstdio>
#include <algorithm>
#include <cctype>
using namespace std;

const int MAXN = 110000;

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

struct Edge{
    int from,to;
    int len,nex;
}edge[MAXN];
int ecnt = 1;int fir[MAXN];
void addedge(int a,int b,int l){
    edge[ecnt] = (Edge){a,b,l,fir[a]};
    fir[a] = ecnt++;
    edge[ecnt] = (Edge){b,a,l,fir[b]};
    fir[b] = ecnt++;
}

//-----

int n,m,q[MAXN],ans[MAXN];
//-----

int f[MAXN],vis[MAXN],siz[MAXN];
int rt,sz;

struct node{
    int d,f;
    bool operator < (node a)const{
        return d < a.d;
    }
}dep[MAXN];
int num;

int search(int d){
    int b = 1,e = num;
    while(e!=b){
        int mid = (b+e)>>1;
        if(dep[mid].d >= d) e = mid;
        else b = mid + 1;
    }
    return b;
}

//-----
void getroot(int nown,int fa){
    siz[nown] = 1,f[nown] = 0;
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to;
        if(vis[v] || v == fa) continue;
        getroot(v,nown);
        siz[nown] += siz[v];
        f[nown] = max(f[nown],siz[v]);
    }
    f[nown] = max(f[nown],sz - siz[nown]);
    if(f[nown] < f[rt]) rt = nown;
}

void getdeep(int nown,int fa,int wh,int d){
    dep[++num] = (node){d,wh};
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to,l = edge[nowe].len;
        if(vis[v] || v == fa) continue;
        getdeep(v,nown,wh,d+l);
    }
}

void work(int nown){
    num = 0;
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to,l = edge[nowe].len;
        if(vis[v]) continue;
        getdeep(v,nown,v,l);
    }
    dep[++num] = (node){0,0};
    sort(dep+1,dep+num+1);

    for(int i = 1;i<=m;i++){
        if(ans[i]) continue;
        int l = 1;
        while(l < num && dep[l].d + dep[num].d < q[i])
            l++;
        while(l < num && 2*dep[l].d < q[i]){
            if(ans[i]) break;
            int t = q[i]-dep[l].d,r = search(t);
            while(r <= num && dep[r].d == t && dep[l].f == dep[r].f)
                r++;
            ans[i] |= (dep[r].d == t);
            l++;
        }
    }
}

void solve(int nown){
    vis[nown] = 1;
    work(nown);
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to;
        if(vis[v]) continue;
        f[rt = 0] = sz = siz[v];
        getroot(v,rt);
        solve(rt);
    }
}

void init(){
    read(n),read(m);
    int a,b,c;
    for(int i = 1;i<=n-1;i++){
        read(a),read(b),read(c);
        addedge(a,b,c);
    }
    for(int i = 1;i<=m;i++)
        read(q[i]);
}

void solve(){
    f[rt = 0] = sz = n;
    getroot(1,rt);
    solve(rt);
    for(int i = 1;i<=m;i++){
        if(ans[i]) print('A'),print('Y'),print('E');
        else print('N'),print('A'),print('Y');
        print('\n');
    }
}

int main(){
    init();
    solve();
    flush();
    return 0;
}