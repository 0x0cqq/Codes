#include <cstdio>
#include <vector>
#include <cstring>
#define min(a,b) ((a)<(b)?(a):(b))
using namespace std;

const int MAXN = 11000;

int n,m,times[MAXN],dfn[MAXN],low[MAXN],instack[MAXN],t,num,c[MAXN],siz[MAXN];

vector<int> edge[MAXN];

struct www{
    int s[MAXN],ttt = 0;
    int top(){
        return s[ttt-1];
    }
    void pop(){
        ttt--;
    }
    void push(int w){
        s[ttt++] = w;
    }
}z;

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

void init(){
    read(n),read(m);
    int a,b;
    for(int i = 1;i<=m;i++){
        read(a),read(b);
        edge[a].push_back(b);
    }
}

void dfs(int nown){
    dfn[nown] = low[nown] = ++t;
    z.push(nown);instack[nown] = 1;
    for(int i:edge[nown]){
        if(dfn[i] == 0)
            dfs(i),low[nown] = min(low[nown],low[i]);
        else if(instack[i])
            low[nown] = min(low[nown],dfn[i]);
    }
    if(dfn[nown] == low[nown]){
        int j = -1;
        do{
            j = z.top(),z.pop();
            instack[j] = 0;
            siz[num]++;
            c[j] = num;
        }while(j!=nown);
        num++;
    }
}

inline void solve(){
    t = 1, num = 0;
    for(int i = 1;i<=n;i++){
        if(dfn[i] == 0)
            dfs(i);
    }
}

inline void check(){
    for(int i = 1;i<=n;i++){
        for(int j = 0;j<edge[i].size();j++){
            if(c[i] != c[edge[i][j]])
                times[c[i]]++;
        }
    }
    int tmp = 0;
    for(int i = 0;i<num;i++){
        if(times[i] == 0){
            if(tmp){
                tmp = 0;break;
            }
            else{
                tmp = siz[i];
            }
        }
    }
    print(tmp);
}

int main(){
    init();
    solve();
    check();
    flush();
    return 0;
}