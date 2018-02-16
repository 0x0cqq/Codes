#include <cstdio>
#include <cstring>
#include <stack>
#include <cctype>
#include <vector>
using namespace std;

const int MAXN = 11000;

namespace fast_IO {
    inline char read() {
//		return getchar();
        static const int IN_LEN = 1000000;
        static char buf[IN_LEN], *s, *t;
        return s==t?t=(s=buf)+fread(buf,1,IN_LEN,stdin),*s++:*s++;
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
    const int OUT_LEN = 10000000;
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
}using namespace fast_IO;

struct Edge{
    int to,len;
    Edge(int t,int l):to(t),len(l){}
};

int n,m,s;

vector<Edge> edge[MAXN]; 

bool vis[MAXN]; 
int times[MAXN],dis[MAXN];
stack<int> q;

bool spfa(){
    memset(dis,0x3f,sizeof(dis));
    dis[s] = 0;q.push(s);vis[s] = 1;
    while(!q.empty()){
        int nown = q.top();q.pop();
        //printf("%d\n",nown);
        if(++times[nown] >= n+1){
            return false;
        }
        vis[nown] = 0;
        for(Edge i:edge[nown]){
            //printf(" nown:%d to:%d len:%d dis[nown]:%d dis[to]:%d\n",nown,i.to,i.len,dis[nown],dis[i.to]);
            if(dis[nown]+i.len < dis[i.to]){
                dis[i.to] = dis[nown]+i.len;
                if(vis[i.to] == 0){
                    q.push(i.to);
                    vis[i.to] = 1;
                }
            }
        }
    }
    return true;
}


int main(){
    read(n),read(m);
    s = n+1;
    for(int i = 1;i<=m;i++){
        int op,a,b,c;
        read(op),read(a),read(b);
        if(op == 1){
            read(c);
            edge[a].push_back(Edge(b,-c));
        }
        else if(op == 2){
            read(c);
            edge[b].push_back(Edge(a,c));
        }
        else{
            edge[b].push_back(Edge(a,0));
            edge[a].push_back(Edge(b,0));
        }
    }
    for(int i = 1;i <= n;i++){
        edge[s].push_back(Edge(i,0));
    }
    if(spfa())
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}