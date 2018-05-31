#include <cstdio>
#include <algorithm>
#include <unistd.h>
using namespace std;

const int MAXN = 300000;

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

struct Splay{
    int val[MAXN],f[MAXN],rev[MAXN];
    int c[MAXN][2],siz[MAXN],root;
    int cnt;
    int newnode(){
        return ++cnt;
    }
    void reverse(int x){
        if(!x) return;
        swap(c[x][0],c[x][1]);
        rev[x] ^= 1;
    }
    void push_down(int x){
        if(!x) return;
        if(rev[x]){
            reverse(c[x][0]),reverse(c[x][1]);
            rev[x] = 0;
        }
    }
    void push_up(int x){
        if(!x) return;    
        siz[x] = siz[c[x][1]] + siz[c[x][0]] + 1;
    } 
    int build(int *a,int l,int r,int fa){
        if(l > r) return 0;
        int ret = newnode(),mid = (l+r)>>1;
        f[ret] = fa,val[ret] = a[mid];
        c[ret][0] = build(a,l,mid-1,ret);
        c[ret][1] = build(a,mid+1,r,ret);
        push_up(ret);
        if(fa == 0) root = ret;
        return ret;
    }
    void rotate(int x){
        push_down(f[x]),push_down(x);
        int y = f[x],z = f[y],t =(c[y][1]==x),w = c[x][1-t];
        c[x][1-t] = y;c[y][t] = w;
        if(z) c[z][c[z][1]==y] = x;
        f[y] = x;f[x] = z;
        if(w) f[w] = y;
        push_up(y),push_up(x);
        if(!f[x]) root = x;
    }
    void splay(int x,int target = 0){
        while(f[x] != target){
            int y = f[x],z = f[y];
            push_down(z),push_down(y);
            if(z!=target){
                if((c[y][1]==x)!=(c[z][1]==y))
                    rotate(x);
                else rotate(y);
            }rotate(x);
        }
    }
    int find(int x,int rank){
        push_down(x);
        if(rank <= siz[c[x][0]])
            return find(c[x][0],rank);
        else if(rank == siz[c[x][0]] + 1)
            return x;
        else
            return find(c[x][1],rank-siz[c[x][0]]-1);
    }
    void reverse(int l,int r){//(l,r)
        int x = find(root,l),y = find(root,r);
        splay(x),splay(y,x);
        reverse(c[y][0]);
    }
    void output(int x,int *a){
        if(!x) return;
        push_down(x);
        output(c[x][0],a);
        a += siz[c[x][0]];*a = val[x];
        output(c[x][1],a+1);
    }
    void __print(int x){
        if(!x) return;
        __print(c[x][0]);
        printf("%d:val:%d c:%d %d fa:%d rev:%d siz:%d\n",x,val[x],c[x][0],c[x][1],f[x],rev[x],siz[x]);
        __print(c[x][1]);
    }
}T;

int n,m,num[MAXN];

void init(){
    read(n),read(m);
    for(int i = 0;i<=n+1;i++)
        num[i] = i;
    T.build(num,0,n+1,0);
}

void solve(){
    int a,b;
    for(int i = 1;i<=m;i++){
        read(a),read(b);
        T.reverse(a,b+2);
    }
    T.output(T.root,num);
    for(int i = 1;i<=n;i++)
        print(num[i]),print(' ');
}

int main(){
    init();
    solve();
    flush();
    return 0;
}
