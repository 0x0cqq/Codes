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

const int MAXN = 510000;

struct Link_Cat_Tree{
    int v[MAXN],sum[MAXN];
    int f[MAXN],c[MAXN][2];
    bool rev[MAXN];
    void push_up(int x){
        sum[x] = sum[c[x][0]] ^ sum[c[x][1]] ^ v[x];
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
    void push_all(int x){
        if(!x) return;
        if(noroot(x)) push_all(f[x]);
        push_down(x);
    }
    bool noroot(int x){
        return (c[f[x]][0] == x || c[f[x]][1] == x);
    }
    void rotate(int x){
        int y = f[x],z = f[y],t = c[y][1]==x,w = c[x][1-t];
        if(noroot(y))c[z][c[z][1]==y] = x;
        c[x][1-t] = y,c[y][t] = w;
        if(w) f[w] = y;
        f[y] = x;f[x] = z;
        push_up(y),push_up(x);
    }
    void splay(int x){
        push_all(x);
        //printf("!\n");
        while(noroot(x)){
            int y = f[x],z = f[y];
            if(noroot(y)){
                if((c[y][1]==x)^(c[z][1]==y))
                    rotate(x);
                else rotate(y);
            }rotate(x);
        }
    }
    void access(int x){
        for(int y = 0;x;x = f[y=x]){
            splay(x);c[x][1] = y;
            push_up(x);
        }
    }
    void makeroot(int x){
        access(x),splay(x),reverse(x);
    }
    void split(int x,int y){
        makeroot(x),access(y),splay(y);
    }
    int find(int x){
        access(x);splay(x);
        push_down(x);
        while(c[x][0])
            x = c[x][0],push_down(x);
        return x;
    }
    void link(int x,int y){
        makeroot(x);
        if(find(y)!=x)
            f[x] = y;
    }
    void cat(int x,int y){
        makeroot(x);//find后y位于树根
        if(find(y) == x && f[x] == y && !c[x][1])
            f[x] = c[y][0] = 0,push_up(y);
    }
    void update(int x,int val){
        makeroot(x);
        //printf("!\n");
        v[x] = val,push_up(x);
    }
    int query(int x,int y){
        return split(x,y),sum[y];
    }
    void print(int n){
        for(int i = 1;i<=n;i++){
            printf("%d: sum:%d v:%d f:%d c:%d %d r:%d\n",i,sum[i],v[i],f[i],c[i][0],c[i][1],int(rev[i]));
        }
    }
};

int n,m;
Link_Cat_Tree w;

void init(){
    read(n),read(m);
    int tmp;
    for(int i = 1;i<=n;i++){
        read(tmp);
        w.update(i,tmp);
    }
}

void solve(){
    int op,a,b;
    for(int i = 1;i<=m;i++){
        read(op),read(a),read(b);
        if(op == 0)
            print(w.query(a,b)),print('\n');
        else if(op == 1)
            w.link(a,b);
        else if(op == 2)
            w.cat(a,b);
        else if(op == 3)
            w.update(a,b);
    }
}

int main(){
    init();
    solve();
    flush();
    return 0;
}