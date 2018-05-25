// luogu-judger-enable-o2
#include <cstdio>
#include <algorithm>
#include <cctype>
using namespace std;

const int MAXN = 210000;

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

namespace prSegTree{
    int f[MAXN*20],ls[MAXN*20],rs[MAXN*20],h[MAXN*20],cnt = 1;
    #define mid ((l+r)>>1)
    void insert(int &nown,int pre,int l,int r,int pos,int fa,int hei){
        nown = ++cnt;ls[nown] = ls[pre],rs[nown] = rs[pre];
        if(l == r)
            f[nown] = fa,h[nown] = hei;
        else{
            if(pos <= mid) insert(ls[nown],ls[pre],l,mid,pos,fa,hei);
            else if(mid+1 <= pos) insert(rs[nown],rs[pre],mid+1,r,pos,fa,hei);
        }
    }
    pair<int,int> query(int nown,int l,int r,int pos){
        if(l == r)
            return make_pair(f[nown],h[nown]);
        else{
            if(pos <= mid) return query(ls[nown],l,mid,pos);
            else if(mid+1 <= pos) return query(rs[nown],mid+1,r,pos);
        }
    }
    void build(int &nown,int l,int r){
        nown = ++cnt;
        if(l == r){
            f[nown] = l,h[nown] = 0;return;
        }
        build(ls[nown],l,mid);
        build(rs[nown],mid+1,r);
    }
}

int n,m;
int rt[MAXN];

void init(){
    read(n),read(m);
    prSegTree::build(rt[0],1,n);
}

int find(int x,int root){
    int w = prSegTree::query(root,1,n,x).first;
    return w == x? x : find(w,root);
}

void solve(){
    int op,a,b,lastans = 0;
    for(int i = 1;i<=m;i++){
        read(op);
        if(op == 1){
            read(a),read(b);
            a^=lastans,b ^= lastans;
            rt[i] = rt[i-1];
            int fa = find(a,rt[i]),fb = find(b,rt[i]);
            if(fa!=fb){
                int ha = prSegTree::query(rt[i],1,n,fa).second,
                    hb = prSegTree::query(rt[i],1,n,fb).second;
                if(ha < hb) swap(ha,hb),swap(fa,fb);
                prSegTree::insert(rt[i],rt[i],1,n,fa,fa,ha==hb?ha+1:ha);
                prSegTree::insert(rt[i],rt[i],1,n,fb,fa,hb);
            }
        }
        else if(op == 2){
            read(a);
            a^=lastans;
            rt[i] = rt[a];
        } 
        else if(op == 3){
            rt[i] = rt[i-1];
            read(a),read(b);
            a^=lastans,b^=lastans;
            int fa = find(a,rt[i]),fb = find(b,rt[i]);
            //printf("%d %d\n",fa,fb);
            lastans = int(fa == fb);
            print(lastans),print('\n');
        }
    }
}

int main(){
    init();
    solve();
    flush();
    return 0;
}