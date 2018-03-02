// luogu-judger-enable-o2
#include <cstdio>
#include <cctype>
using namespace std;

const int MAXN = 200000;

namespace fast_io {
    inline char read();
    inline void read(int&);
//  inline void read(char*);
    inline void print(char);
    inline void print(int);
//  inline void print(char*);
    inline void flush();
    inline char read() {
//		return getchar();
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
            	x = (x + (x << 2) << 1) + (c ^ '0');
        if (iosig) x = -x;
    }
    
    inline void read(char *a){
        static char c = read();
        while(c != -1&&(c == ' '||c == '\n')){
            c = read();
        }
        while(c!= -1&&c!=' '&&c!='\n'){
            *a++ = c;
            c = read();
        }
        *a = 0;
    }
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

int maxn[MAXN<<2],n,d,len,M;

void init(){
    read(n),read(d);//read();
    len = 1;
    for(M = 1;M <= n+2;M<<=1);
}

inline void push_up(int nown){
    maxn[nown] = maxn[nown<<1]>maxn[nown<<1|1]?maxn[nown<<1]:maxn[nown<<1|1];
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

inline void add(int num){
    int pos = len + M;
    maxn[pos] = num;
    for(pos>>=1;pos;pos>>=1) push_up(pos);
    len++;
}

inline void solve(){
    char op[20];int a,b,last = 0;
    for(int i = 1;i<=n;i++){
        read(op);
        print(':'),print(op[0]),print('\n');
        read(a);//read();
        if(op[0] == 'A'){
            a+=last;a%=d;
            add(a);
        }
        else if(op[0] =='Q'){
            if(a == 0) last = 0;
            else last = query(len-a,len-1);
            print(last),print('\n');
        }
    }
}

int main(){
    init();
    solve();
    flush();
    return 0;
}