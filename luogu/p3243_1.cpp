#include <cstdio>
#include <vector>
#include <unistd.h>
#include <cctype>
#include <queue>
#include <cstring>
#include <algorithm>
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
            	x = ((x+(x<<2))<<1) + (c ^ '0');
        if (iosig) x = -x;
    }
    /*
    inline void read(char *a){
        static char c = read();
        while(c!= -1&&(c == ' '||c =='\n')){
            c = read();
        }
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
    inline void print(char *a){
        while(*a) print(*(a++));
    }
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
    inline void print(char *x){
        printf("%s",x);
    }
    inline void flush(){
        return;
    }
}//using namespace normal_io;

int n,m;

int fir[MAXN],to[MAXN],nex[MAXN];

char im[20] = "Impossible!";

void addedge(int u,int v,int cnt){
    nex[cnt] = fir[u];
    fir[u] = cnt;
    to[cnt] = v;
}

void init(){
    read(n),read(m);
    memset(fir,0,sizeof(fir));
    int a,b;
    for(int i = 1;i<=m;i++){
        read(a),read(b);
        addedge(b,a,i);
    }
}

priority_queue<int> q;

void solve(){
    static int tmp[MAXN],out[MAXN],tmpcnt;

    tmpcnt = 0;
    memset(out,0,sizeof(out));
    while(!q.empty())
        q.pop();

    for(int i = 1;i<=n;i++)
        for(int nowe = fir[i];nowe;nowe = nex[nowe])
            out[to[nowe]]++;
    for(int i = 1;i<=n;i++)
        if(out[i] == 0)
            q.push(i);
    while(!q.empty()){
        int nown = tmp[tmpcnt++] = q.top();q.pop();
        for(int nowe = fir[nown];nowe;nowe = nex[nowe]){
            int t = to[nowe];
            if(--out[t] == 0)
                q.push(t); 
        }
    }
    if(tmpcnt!=n)
        print(im);
    else
        for(int i = tmpcnt-1;i>=0;i--)
            print(tmp[i]),print(' ');
    print('\n');

}

int main(){
    int T;
    read(T);
    for(int i = 1;i<=T;i++){
        init();
        solve();
    }
    flush();
    return 0;
}