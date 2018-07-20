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

const int MAXN = 500000;

namespace Merge_Heap{
int v[MAXN],l[MAXN],r[MAXN],d[MAXN],f[MAXN];
bool vis[MAXN];
int __merge(int x,int y){
    if(x == y) return x;
    if(!x || !y) return x+y;
    if(v[x] > v[y] || (v[x] == v[y] && x > y))
        swap(x,y);
    r[x] = __merge(r[x],y);
    f[r[x]] = x;// 维护父亲
    if(d[l[x]] < d[r[x]])
        swap(l[x],r[x]);
    d[x] = d[r[x]] + 1;
    return x;
}
int __pop(int x){
    f[l[x]] = f[r[x]] = 0;
    return __merge(l[x],r[x]);
}
int __find(int x){
    while(f[x]) x = f[x];
    return x;
}
void init(int n,int *num){
    for(int i = 1;i<=n;i++)
        v[i] = num[i];
}
void merge(int x,int y){
    if(vis[x]||vis[y]) return;
    __merge(__find(x),__find(y));
}
int pop(int x){
    if(vis[x]) return -1;
    int w = __find(x);
    vis[w] = 1;
    __pop(w);
    return v[w];
}
}

int n,m,num[MAXN];

void init(){
    read(n),read(m);
    for(int i = 1;i<=n;i++)
        read(num[i]);
    Merge_Heap::init(n,num);
}

void solve(){
    int op,x,y;
    for(int i = 1;i<=m;i++){
        read(op),read(x);
        if(op == 1)
            read(y),Merge_Heap::merge(x,y);
        else if(op == 2)
            print(Merge_Heap::pop(x)),print('\n');
    }
}

int main(){
    init();
    solve();
    flush();
    return 0;
}