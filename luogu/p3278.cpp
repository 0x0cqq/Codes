#include <cstdio>
#include <unistd.h>
#include <cctype>
#define ll long long
using namespace std;

const int MAXN = 210000;
const ll p = 20130426LL;

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

inline void mod(ll &x){x %= p;}

struct Splay{
    ll val[MAXN],addn[MAXN],muln[MAXN];
    int f[MAXN],c[MAXN][2],siz[MAXN],tot,root;
    int newnode(int v = 0){
        val[++tot] = v;
        siz[tot] = 1;
        addn[tot] = 0,muln[tot] = 1;
        return tot;     
    }
    void add(int x,int num){
        if(!x) return;
        addn[x] += num,val[x] += num;
        mod(val[x]),mod(addn[x]);
    }
    void mul(int x,int num){
        if(!x) return;
        muln[x] *= num,addn[x] *= num,val[x] *= num;
        mod(addn[x]),mod(muln[x]),mod(val[x]);
    }
    void push_down(int x){
        if(!x) return;
        if(muln[x]!=1){
            mul(c[x][0],muln[x]);
            mul(c[x][1],muln[x]);
            muln[x] = 1;
        }
        if(addn[x] != 0){
            add(c[x][0],addn[x]);
            add(c[x][1],addn[x]);
            addn[x] = 0;
        }
    }
    void  push_up(int x){
        if(!x) return;
        siz[x] = siz[c[x][0]] + siz[c[x][1]] + 1;
    }
    void rotate(int x){
        int y = f[x],z = f[y],t = (c[y][1]==x),w = c[x][1-t];
        push_down(y),push_down(x);
        f[x] = z;f[y] = x;
        if(w) f[w] = y;
        c[x][1-t] = y,c[y][t] = w;
        if(z) c[z][c[z][1]==y] = x;
        push_up(y),push_up(x);
        if(!f[x]) root = x;
    }
    void splay(int x,int target = 0){
        while(f[x]!=target){
            int y = f[x],z = f[y];
            if(z!=target)
                (c[z][1]==y) ^ (c[y][1]==x)?rotate(x):rotate(y);
            rotate(x);
        }
    }
    int qrank(int r){
        int x = root;
        while(2333){
            if(r <= siz[c[x][0]])
                x = c[x][0];
            else if(r == siz[c[x][0]] + 1)
                break;
            else
                r -= siz[c[x][0]] + 1,x = c[x][1];
        }
        return x;
    }
    int __build(int l,int r,int fa){
        if(l > r) return 0;
        int mid = (l+r)>>1;
        int x = newnode();
        f[x] = fa;
        c[x][0] = __build(l,mid-1,x);
        c[x][1] = __build(mid+1,r,x);
        push_up(x);
        return x;
    }
    void build(int num){
        root = __build(1,num,0);
    }
    void __output(int x,ll *a){
        if(!x) return;
        push_down(x);
        __output(c[x][0],a);
        a += siz[c[x][0]],*a = val[x];
        __output(c[x][1],a+1);
    }
    void output(ll *a){
        __output(root,a);
    }
    void add(int l,int r,int num){
        int lb = qrank(l),rb = qrank(r+2);
        //printf("%d %d\n",lb,rb);
        splay(lb),splay(rb,lb);
        add(c[rb][0],num);
        push_up(rb),push_up(lb);
    }
    void mul(int l,int r,int num){
        int lb = qrank(l),rb = qrank(r+2);
        splay(lb),splay(rb,lb);
        mul(c[rb][0],num);
        push_up(rb),push_up(lb);
    }
    void mulx(int l,int r){
        int x = qrank(l),y = qrank(l+1),z = qrank(r+1),a = qrank(r+2),b = qrank(r+3);
        //printf("mulx: x:%d y:%d z:%d a:%d b:%d\n",x,y,z,a,b);
        splay(z),splay(b,z);
        c[b][0] = 0;push_up(b),push_up(z);
        val[z] += val[a];
        splay(x),splay(y,x);
        c[y][0] = newnode(),f[c[y][0]] = y;
        push_up(y),push_up(x);
    }
    void __print(int x,int depth){
        if(depth == 0) printf("--------------------\n");
        if(!x) return;
        __print(c[x][0],depth+1);
        for(int i = 0;i<depth;i++) putchar(' ');
        printf("%d:siz:%d | val:%lld add:%lld mul:%lld c:%d %d f:%d\n",x,siz[x],val[x],addn[x],muln[x],c[x][0],c[x][1],f[x]);
        __print(c[x][1],depth+1);
        if(depth == 0) printf("--------------------\n");
    }
    void print(){
        __print(root,0);
    }
}T;

int n,m = 110000;

ll query(ll v){
    static ll o[MAXN];
    T.output(o);
    ll ans = 0;
    for(int i = m;i>=1;i--){
        ans = ans * v + o[i];
        //printf("o[i]:%lld,ans:%lld\n",o[i],ans);
        mod(ans);
    }
    return ans;
}


void init(){
    read(n);
    T.build(m+3);
    //printf("finish building\n");
}

void solve(){
    char op[10];int l,r,v;
    for(int i = 1;i<=n;i++){
        read(op);
        if(op[0] == 'q'){
            read(v);
            print(int(query(v))),print('\n');
        }
        else if(op[0] == 'p')
            T.print(),--i;
        else{
            read(l),read(r);
            if(op[3] == 'x')
                T.mulx(l+1,r+1);
            else{
                read(v);
                if(op[0] == 'm')
                    T.mul(l+1,r+1,v);
                else if(op[0] == 'a')
                    T.add(l+1,r+1,v);
            }
        }
        //printf("finish\n");
    }
}

int main(){
    init();
    solve();
    flush();
    return 0;
}