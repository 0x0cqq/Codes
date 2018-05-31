#include <cstdio>
#include <algorithm>
#include <cctype>
using namespace std;

const int MAXN = 210000,logn = 20;
int n,m;

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

namespace BCJ{
    int f[MAXN],siz[MAXN];
    int find(int x){
        return f[x] == x?x:f[x] = find(f[x]);
    }
    void un(int x,int y){
        int fx = find(x),fy = find(y);
        if(fx!=fy){
            siz[fx] += siz[fy];
            f[fy] = fx;
        }
    }
    void init(){
        for(int i = 1;i<=n;i++){
            f[i] = i,siz[i] = 1;
        }
    }
}

namespace Splay{
    int val[MAXN],c[MAXN][2],siz[MAXN];
    int f[MAXN],cnt,root[MAXN];
    void push_up(int x){
        if(!x) return;
        siz[x] = siz[c[x][1]] + siz[c[x][0]] + 1;
    }
    void rotate(int x){
        if(!x) return;
        int y = f[x],z = f[y],t = (c[y][1]==x),w = c[x][1-t];
        if(z) c[z][c[z][1]==y] = x;
        c[x][1-t] = y;c[y][t] = w;
        if(w) f[w] = y;
        f[y] = x;f[x] = z;
        push_up(y),push_up(x);
        if(!f[x]) root[BCJ::find(x)] = x;
    }
    void splay(int x,int target = 0){
        while(f[x]!=target){
            int y = f[x],z = f[y];
            if(z!=target){
                (c[z][1]==y)^(c[y][1]==x)?rotate(x):rotate(y);
            }rotate(x);
        }
    }
    void insert(int num,int tree){
        int x = root[tree],fa = 0;
        if(!x){
            root[tree] = num;
            siz[num] = 1,c[num][0] = c[num][1] = f[num] = 0;
            return;
        }
        while(x)
            siz[x]++,fa = x,x = c[x][val[x]<val[num]];
        x = num;
        if(fa) c[fa][val[fa]<val[num]] = x;
        f[x] = fa,c[x][0] = c[x][1] = 0,siz[x] = 1;
        splay(x);
    }
    int qrank(int r,int tree){
        if(r > siz[root[tree]]) return -1;
        int x = root[tree];
        while(2333){
            if(r <= siz[c[x][0]])
                x = c[x][0];
            else if(r == siz[c[x][0]] + 1)
                break;
            else
                r -= siz[c[x][0]] + 1,x = c[x][1];
        }
        splay(x);
        return x;
    }
    void output(int *a,int x){
        if(!x) return;
        output(a,c[x][0]);
        a[siz[c[x][0]]] = x;
        a += siz[c[x][0]] + 1;
        output(a,c[x][1]);
    }
    void __print(int x,int depth = 0){
        if(depth == 0) printf("%d:-----------------\n",x);
        if(x){
            __print(c[x][0],depth+1);
            for(int i = 0;i<depth;i++) putchar(' ');
            printf("%d val:%d c:%d %d f:%d siz:%d\n",x,val[x],c[x][0],c[x][1],f[x],siz[x]);
            __print(c[x][1],depth+1);
        }
        if(depth == 0) printf("-----------------\n");
    }
    void print(){
        for(int i = 1;i<=n;i++){
            if(BCJ::find(i) == i)
                printf("root:%d ",i),__print(root[i]);
        }
    }
}

void build(int x,int y){
    int fx = BCJ::find(x),fy = BCJ::find(y);
    //printf("x:%d y:%d fx:%d fy:%d\n",x,y,fx,fy);
    if(fx==fy)
        return;
    if(BCJ::siz[fx] < BCJ::siz[fy]) swap(fx,fy);
    BCJ::un(fx,fy);
    static int o[MAXN];int nn = BCJ::siz[fy];
    Splay::output(o,Splay::root[fy]);
    for(int i = 0;i<nn;i++)
        Splay::insert(o[i],fx);
    //if(flag) swap(Splay::root[fy],Splay::root[fx]);
}

int query(int x,int r){
    return Splay::qrank(r,BCJ::find(x));
}

void init(){
    read(n),read(m);
    int a,b;
    BCJ::init();
    for(int i = 1;i<=n;i++){
        read(a);
        Splay::val[i] = a;
    }
    for(int i = 1;i<=n;i++){
        Splay::root[i] = i;
        Splay::siz[i] = 1;
    }
    for(int i = 1;i<=m;i++){
        read(a),read(b);
        build(a,b);
    }
}

void solve(){
    read(m);
    char op[10];int x,r;
    for(int i = 1;i<=m;i++){
        read(op),read(x),read(r);
        if(op[0] == 'Q')
            print(query(x,r)),print('\n');
        else if(op[0] == 'B')
            build(x,r);
        else if(op[0] == 'P')
            Splay::print();
    }
}

int main(){
    init();
    solve();

    return 0;
}