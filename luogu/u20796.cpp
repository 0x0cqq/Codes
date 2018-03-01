#include <cstdio>
#include <cctype>
using namespace std;

namespace fast_io {
    inline char read();
    inline void read(int&);
    //  inline void read(char*);
    inline void print(char);
    inline void print(int);
    //  inline void print(char*);
    inline void flush();
    inline char read() {
    //	return getchar();
        static const int IN_LEN = 1000000;
        static char buf[IN_LEN], *s, *t;
        return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))== s)?-1:*s++) : *s++;
    }
    inline void read(int &x) {
        static bool iosig;
        static char c;
        for (iosig = false, c = read(); !isdigit(c); c = read()) {
            if (c == '-') iosig = true;
            if (c == -1) return;
        }
        for (x = 0; isdigit(c); c = read())
            x = (x << 1) + (x << 3) + (c ^ '0');
        if (iosig) x = -x;
    }
    /*
    inline void read(char *a){
        static char c = read();
        while(c!= -1&&c!=' '&&c!='\n'){
            *a++ = c;
            c = read();
        }
        *a = 0;
    }*/
    const int OUT_LEN = 1000000;
    char obuf[OUT_LEN], *ooh = obuf;
    inline void print(char c) {
        if (ooh == obuf + OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), ooh = obuf;
        *ooh++ = c;
    }
    inline void print(int x) {
        static int buf[30], cnt;
        if (x == 0) {
            print('0');
        }
        else {
            if (x < 0) print('-'), x = -x;
            for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + 48;
            while (cnt) print((char)buf[cnt--]);
        }
    }
    /*
    inline void print(char *a){
        while(*a) print(*a++);
    }
    */
    inline void flush() {
        fwrite(obuf, 1, ooh - obuf, stdout);
    }
}using namespace fast_io;

namespace normal_io{
    inline char read(){
        return getchar();
    }
    inline void read(int &x){
        scanf("%d",&x);
    }
    inline void print(int x){
        printf("%d",x);
    }
    inline void print(char x){
        putchar(x);
    }
    inline void flush(){
        return;
    }
}//using namespace normal_io;

const int MAXN = 1000000;

int maxn[MAXN<<2],n,m,M;

inline void push_up(int nown){
    maxn[nown] = maxn[nown<<1]>maxn[nown<<1|1]?maxn[nown<<1]:maxn[nown<<1|1];
}

void init(){
    read(n),read(m);//read();
    for(M = 1;M <= n+2;M<<=1);
    for(int i = 1;i<=n;i++){
        read(maxn[M+i]);
    }
    for(int i = M-1;i;i--){
        push_up(i);
    }
}

inline int query(int l,int r){
    int ans = 0;
    for(l=M+l-1,r=M+r+1;l^r^1;l>>=1,r>>=1){
        if(~l&1)
            if(maxn[l^1]>ans) ans = maxn[l^1];
        if(r&1) 
            if(maxn[r^1]>ans) ans = maxn[r^1];
    }
    return ans;
}

inline void update(int pos,int num){
    pos += M;
    maxn[pos] = num;
    for(pos>>=1;pos;pos>>=1) push_up(pos);
}

inline void solve(){
    int op,a,b,last = 0;
    for(int i = 1;i<=m;i++){
        read(op),read(a),read(b);//read();
        if(op == 1)
            update(a,b);
        else if(op == 2)
            print(query(a,b)),print('\n');
    }
}

int main(){
    freopen("1.txt","r",stdin);
    freopen("1.out","w",stdout);
    init();
    solve();
    flush();
    return 0;
}