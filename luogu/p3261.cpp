#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>
typedef long long ll;
using namespace std;

namespace fast_io{
    static const int SIZE=1024*1024;char ibuf[SIZE],*_s,*_t,obuf[SIZE],*oh=obuf;inline void flush(){fwrite(obuf,1,oh-obuf,stdout);}
    inline char read(){if(_s==_t)_t=(_s=ibuf)+fread(ibuf,1,SIZE,stdin);return _s==_t?-1:*_s++;}
    template<typename T>inline void read(T&x){static char c;static bool iosig;for(iosig=0,c=read();!isdigit(c);c=read()){if(c==-1)return;iosig|=(c=='-');}for(x=0;isdigit(c);c=read())x=(((x<<2)+x)<<1)+(c^48);if(iosig)x=-x;return;}
    inline void read(char*a){static char c=read();while(c!=-1&&(c==' '||c!='\r'||c=='\n'))c=read();while(c!=-1&&c!=' '&&c!='\r'&&c!='\n')*a++=c,c=read();*a=0;}
    inline void print(char c){if(oh==obuf+SIZE)fwrite(obuf,1,SIZE,stdout),oh=obuf;*oh++=c;}
    template<typename T>inline void print(T x){static int buf[21],cnt;if(!x)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while(cnt)print((char)buf[cnt--]);}}
    inline void print(char*a){while(*a)print(*a++);}
}using namespace fast_io;

const int MAXN = 310000;

namespace MH{
int l[MAXN],r[MAXN],d[MAXN];
ll v[MAXN],addn[MAXN],muln[MAXN];
inline void add(int x,ll val){
    if(!x) return;
    v[x]+=val,addn[x]+=val;
}
inline void mul(int x,ll val){
    if(!x) return;
    v[x]*=val,addn[x]*=val,muln[x] *= val;
}
inline void push_down(int x){
    if(!x) return;
    if(muln[x]!=1){
        mul(l[x],muln[x]),mul(r[x],muln[x]);
        muln[x] = 1;
    }
    if(addn[x]){
        add(l[x],addn[x]),add(r[x],addn[x]);
        addn[x] = 0;
    }
}
inline int merge(int x,int y){
    if(x == y) return x;
    if(!x || !y) return x+y;
    if(v[x] > v[y]) swap(x,y);
    push_down(x);
    r[x] = merge(r[x],y);
    if(d[l[x]] < d[r[x]]) swap(l[x],r[x]);
    d[x] = d[r[x]] + 1;
    return x;
}
inline ll top(int x){
    return v[x];
}
inline int del(int x){
    push_down(x);
    int t = merge(l[x],r[x]);
    l[x] = r[x] = d[x] = 0;
    return t;
}
inline void init(int n,ll *num){
    for(int i = 1;i<=n;i++)
        v[i] = num[i],l[i] = r[i] = d[i] = addn[i] = 0,muln[i] = 1;
}
}

int n,m,root;
ll h[MAXN];
int f[MAXN],a[MAXN];ll v[MAXN];
ll s[MAXN];int c[MAXN],dep[MAXN];
int ans1[MAXN],ans2[MAXN];
vector<int> edge[MAXN];
vector<int> st[MAXN];

void init(){
    read(n),read(m);
    for(int i = 1;i<=n;i++)
        read(h[i]);
    for(int i = 2;i<=n;i++){
        read(f[i]),read(a[i]),read(v[i]);
        edge[f[i]].push_back(i);
    }
    for(int i = 1;i<=m;i++){
        read(s[i]),read(c[i]);
        st[c[i]].push_back(i);
    }
    root = m+1;
    edge[root].push_back(1);
    h[root] = (long long)(1e18);
    MH::init(m,s);
}

int dfs(int nown){
    int ans = 0,tmp = 0;
    for(int i = 0;i < edge[nown].size();i++){
        int v = edge[nown][i];
        dep[v] = dep[nown] + 1;
        tmp = dfs(v);
        ans = MH::merge(ans,tmp);
    }
    for(int i = 0;i<st[nown].size();i++)
       ans = MH::merge(st[nown][i],ans);
    while(MH::top(ans) < h[nown] && ans!=0){
        ans1[nown]++;
        tmp = ans;
        ans2[tmp] = dep[c[tmp]] - dep[nown];
        ans = MH::del(ans);
    }
    if(a[nown] == 0)
        MH::add(ans,v[nown]);
    else if(a[nown] == 1)
        MH::mul(ans,v[nown]);
    return ans;
}

void output(){
    for(int i = 1;i<=n;i++)
        print(ans1[i]),print('\n');
    for(int i = 1;i<=m;i++)
        print(ans2[i]),print('\n');
}

signed main(){
    init();
    dfs(root);
    output();
    flush();
    return 0;
}