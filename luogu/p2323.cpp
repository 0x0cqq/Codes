#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#define pp pair<int,int>
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
    int id;
    int u,v,l;
    bool operator < (Edge b)const{
        return l < b.l;
    }
    Edge(int i = 0,int a = 0,int b = 0,int c = 0){
        id = i,u = a,v = b,l = c;
    }
};

const int MAXN = 15000;

int n,k,m,maxc = 1;
int f[MAXN];
bool vis[MAXN];

void init_b(){
    for(int i = 1;i<=n;i++){
        f[i] = i;
    }
}

int find(int x){
    return f[x] == x?x:f[x] = find(f[x]);
}

Edge high[MAXN<<1],low[MAXN<<1];

void init(){
    read(n),read(k),read(m);
    int a,b,c1,c2;
    for(int i = 1;i<=m;i++){
        read(a),read(b),read(c1),read(c2);
        high[i] = Edge(i,a,b,c1);
        low[i] = Edge(i,a,b,c2);
        maxc = max(c1,maxc);
    }
    sort(high+1,high+m+1),sort(low+1,low+m+1);
}

bool judge(int limit){
    init_b();
    memset(vis,0,sizeof(vis));
    int cnt = 0;
    for(int i = 1;i<=m;i++){
        if(high[i].l > limit || cnt == n-1) break;
        int x1 = find(high[i].u),y1 = find(high[i].v);
        if(x1!=y1){
            f[x1] = y1;
            vis[high[i].id] = 1;
            cnt++;
        }
    }
    if(cnt<k) return false;
    for(int i = 1;i<=m;i++){
        if(low[i].l > limit || cnt == n-1)
            break;
        if(vis[low[i].id]) continue;
        int x1 = find(low[i].u),y1 = find(low[i].v);
        if(x1!=y1){
            f[x1] = y1;
            cnt++;
        }              
    }
    return cnt == n-1;
}



void solve(){
    int b = 1,e = maxc+1;
    while(b!=e){
        int mid = (b+e)/2;
        int flag = judge(mid);
        if(flag) e = mid;
        else b = mid+1;
    }
    print(b),print('\n');
}

int main(){
    init();
    solve();
    flush();
    return 0;
}