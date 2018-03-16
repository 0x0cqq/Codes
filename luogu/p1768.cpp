#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 7100;

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
    /*
    inline void print(char *a){
        while(*a) print(*a++);
    }
    */
    inline void flush() {
        fwrite(obuf, 1, ooh - obuf, stdout);
    }
}using namespace fast_io;

struct Edge{
    int t,v,p;
    double l;
    Edge(int to = 0,int val = 0,int price = 0):t(to),v(val),p(price),l(0){}
};

int n,m,cc;
vector<Edge> edge[MAXN];

void init(){
    read(n),read(m);
    cc = 500;
    int a,b,c,d;
    for(int i = 1;i<=m;i++){
        read(a),read(b),read(c),read(d);
        edge[a].push_back(Edge(b,c,d));
    }
    for(int i = 1;i<=n;i++){
        edge[0].push_back(Edge(i,0,0));
    }
}

void set_to(double bizhi){
    for(int i = 0;i<=n;i++){
        for(int j = 0;j<edge[i].size();j++){
            edge[i][j].l = bizhi*edge[i][j].p - edge[i][j].v;
        }
    }
}

bool instack[MAXN];
double dis[MAXN];
int times[MAXN];

bool judge(){
    int s = 0;
    memset(times,0,sizeof(times));
    memset(instack,0,sizeof(instack));
    queue<int> q;
    q.push(s);
    dis[s] = -1;
    while(!q.empty()){
        int nown = q.front();q.pop();
        instack[nown] = 0;
        if(++times[nown] > cc)
            return true;
        for(int i = 0;i<edge[nown].size();i++){
            int to = edge[nown][i].t;
            double len = edge[nown][i].l;
            if(dis[to] > dis[nown] + len){
                dis[to] =  dis[nown] + len;
                if(!instack[to])
                    q.push(to);
            }
        }
    }
    return false;
}

void solve(){
    double b = 0,e = 200;
    while(e-b>1e-2){
        double mid = (b+e)/2;
        set_to(mid);
        int flag = judge();
        if(!flag) e = mid;
        else b = mid;
    }
    if(b!=0)
        printf("%.1lf\n",b);
    else
        printf("-1\n");
}

int main(){
    init();
    solve();
    return 0;
}