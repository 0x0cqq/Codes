#include <cstdio>
#include <cctype>
using namespace std;
#define lson (nown<<1)
#define rson ((nown<<1)|1)
#define mid ((l+r)>>1)
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
}//using namespace fast_io;

namespace normal_io{
    inline char read(){return getchar();}
    inline void read(int &x){scanf("%d",&x);}
    inline void read(char *x){scanf("%s",x);}
    inline void print(int x){printf("%d",x);}
    inline void print(char x){putchar(x);}
    inline void flush(){return;}
}using namespace normal_io;


namespace seg_tree{
struct node{
    int sum;
    int lc,rc;
    int lazy;
}t[MAXN<<2];

node merge(const node l,const node r){
    node ret = (node){l.sum + r.sum,l.lc,r.rc,0};
    if(l.rc == r.lc) ret.sum--;
    return ret;
}

void push_down(int nown){
    if(t[nown].lazy){
        int tmp = t[nown].lazy;
        t[lson].lazy = t[rson].lazy = tmp;
        t[lson].lc = t[rson].lc = tmp;
        t[lson].rc = t[rson].rc = tmp;
        t[lson].sum = t[rson].sum = 1;
        t[nown].lazy = 0;
    }
}

void update(int nown,int l,int r,int ql,int qr,int c){
    if(l <= ql && qr <= r){
        t[nown].lc = t[nown].rc = t[nown].lazy = c;
        t[nown].sum = 1;
    }
    else{
        push_down(nown);
        if(ql<=mid && mid+1<=qr)
            update(lson,l,mid,ql,qr,c),update(rson,mid+1,r,ql,qr,c);
        else if(ql <= mid)
            update(lson,l,mid,ql,qr,c);
        else if(qr >= mid+1)
            update(rson,mid+1,r,ql,qr,c);
        t[nown] = merge(t[lson],t[rson]);
    }
}

void build(int nown,int l,int r,int *num){
    if(l == r){
        t[nown] = (node){1,num[l],num[l],0};
    }
    else{
        build(lson,l,mid,num);
        build(rson,mid+1,r,num);
        t[nown] = merge(t[lson],t[rson]);
    }
}
}

int n,m,num[MAXN];

void init(){
    read(n),read(m);
    for(int i = 1;i<=n;i++){
        read(num[i]);
    }
    seg_tree::build(1,1,n,num);
}

void solve(){
    int op,a,b,c;
    for(int i = 1;i<=m;i++){
        read(op);
        if(op == 1){
            read(a),read(b),read(c);
            seg_tree::update(1,1,n,a,b,c);
        }
        else if(op == 2){
            print(seg_tree::t[1].sum),print('\n');
        }
    }
}

int main(){
    init();
    solve();
    flush();
    return 0;
}