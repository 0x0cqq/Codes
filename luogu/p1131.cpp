#include <cstdio>
#include <vector>
#include <cctype>
#include <algorithm>
#define int long long
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
        scanf("%lld",&x);
    }
    inline void print(int x){
        printf("%lld",x);
    }
    inline void print(char x){
        putchar(x);
    }
    inline void flush(){
        return;
    }
}//using namespace normal_io;

const int MAXN = 510000;

int n,s;

struct Edge{
    int t,l;
    Edge(int b = 0,int c = 0):t(b),l(c){};
};

vector<Edge> edge[MAXN];

int ans[MAXN],times[MAXN];

bool vis[MAXN];

void addedge(int a,int b,int c){
    edge[a].push_back(Edge(b,c));
    edge[b].push_back(Edge(a,c));
}

void init(){
    read(n),read(s);
    int a,b,c;
    for(int i = 1;i<=n-1;i++){
        read(a),read(b),read(c);
        addedge(a,b,c);
    }
}

void dp(int nown){
    vis[nown] = 1;
    int tmpsum = 0,mintime = 0,k = 0;
    for(int i = 0;i<edge[nown].size();i++){
        int to = edge[nown][i].t,len = edge[nown][i].l;
        if(vis[to] == 1)
            continue;
        dp(to);
        ans[nown] += ans[to];
        mintime = max(mintime,times[to]+len);
        tmpsum += (times[to]+len);
        k++;
    }
    ans[nown] += k * mintime - tmpsum,times[nown] = mintime;
    //print(nown),print(' '),print(times[nown]),print(' '),print(ans[nown]),print('\n');
}

void solve(){
    dp(s);
    print(ans[s]);
}

main(){
    init();
    solve();
    flush();
    return 0;
}