#include <cstdio>
#include <cctype>
#include <cstring>
#include <vector>
#define int long long
using namespace std;

namespace fast_io {
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
    inline void flush() {
        fwrite(obuf, 1, ooh - obuf, stdout);
    }
}using namespace fast_io;

const int MAXN = 110000;

struct Edge{
    int to,len;
    Edge(int t = 0,int l = 0):to(t),len(l){};
};

int n,m,s;
vector<Edge> edge[MAXN];

int num[MAXN<<2],tail = 0;
inline bool empty(){
    return tail == 0;
}
inline void push(int x){
    num[tail++] = x;
}
inline int front(){
    return num[tail-1];
}
inline void pop(){
    tail--;
}

bool instack[MAXN];

int dis[MAXN];
int times[MAXN],c;

bool spfa(){
    push(s);
    while(!empty()){
        int nown = front();pop();
        instack[nown] = 0;
        if((times[nown]++)>c) return false;
        for(int i = 0;i<edge[nown].size();i++){
            int to = edge[nown][i].to,len = edge[nown][i].len;
            if(dis[to] < dis[nown]+len){
                dis[to] = dis[nown]+ len;
                if(!instack[to]) push(to);
                instack[to] = 1;
            }
        }
    }
    return true;
}

void addedge(int f,int t,int l){
    edge[f].push_back(Edge(t,l));
}

void init(){
    read(n),read(m);s = n+1;
    int op,a,b;
    for(int i = 1;i<=m;i++){
        read(op),read(a),read(b);
        if(op == 1)
            addedge(a,b,0),addedge(b,a,0);
        else if(op == 2)
            addedge(a,b,1);
        else if(op == 3)
            addedge(b,a,0);
        else if(op == 4)
            addedge(b,a,1);
        else if(op == 5)
            addedge(a,b,0);
    }
    for(int i = n;i>=1;i--)
        addedge(s,i,1);
}

void solve(){
    c = 80000;
    bool flag = spfa();
    if(flag == 0)
        print(-1LL),print('\n');
    else{
        int sumn = 0;
        for(int i = 1;i<=n;i++)
            sumn += dis[i];
        print(sumn),print('\n');
    }
}

main(){
    init();
    solve();
    flush();
    return 0;
}