#include <cstdio>
#include <cctype>
#include <algorithm>
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

const int MAXN = 1100;

int n,m,p,coin[MAXN][MAXN],cost[MAXN],ans[MAXN];

//第一维是点，第二维是时间

void init(){
    read(n),read(m),read(p);
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            read(coin[i][j]);
            coin[i][j]+=coin[i-1][j-1];
        }
    }
    for(int i = 1;i<=n;i++){
        read(cost[i]);
    }
}

inline int cal(int ti,int start,int ppp){
    int res = 0;
    res-=cost[start];
    //printf("!!!:%d %d %d\n",ti,start,ppp);
    while(ppp>0){
        //printf(":%d %d %d\n",ti,start,ppp);
        if(start+ppp-1<=n){
            res+=coin[start+ppp-1][ti+ppp-1]-coin[start-1][ti-1];
            ppp = 0;
        }
        else{
            res+=coin[n][ti+n-start]-coin[start-1][ti-1];
            ppp -= n-start+1;
            ti = ti+n-start+1;
            start = 1;
        }
    }
    //printf("ans:%d\n",res);
    return res;
}

void solve(){
    ans[1] = 0;
    for(int t = 2;t<=m+1;t++){
        ans[t] = -0x3f3f3f3f;
        for(int nowp = 1;nowp<=p;nowp++){
            if(nowp>=t) break;
            for(int i = 1;i<=n;i++){
                ans[t] = max(ans[t],ans[t-nowp]+cal(t-nowp,i,nowp));
            }
        }
        //printf("%d\n",ans[t]);
    }
    print(ans[m+1]);
}


int main(){
    init();
    solve();
    flush();
    return 0;

}