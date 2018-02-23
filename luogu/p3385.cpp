#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

namespace fast_IO{
    inline char read(){
        static const int IN_LEN = 1000000;
        static char buf[IN_LEN],*s,*t;
        return s==t?(t=(s=buf)+fread(buf,1,IN_LEN,stdin)) == s?-1:*s++:*s++; 
    }
    inline void read(int &x){
        static bool iosig;
        static char c;
        for(iosig = 0,c = read();!isdigit(c);c = read()){
            if(c == '-') iosig = true;
            if(c == -1) return;
        }
        for(x = 0;isdigit(c);c = read())
            x = (x<<1)+(x<<3)+(c^'0');
        if(iosig) x = -x;
    }
    const int OUT_LEN = 1000000;
    char obuf[OUT_LEN],*ooh = obuf;
    inline void print(char c){
        if(ooh == obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh = obuf;
        *ooh++ = c;
    }
    inline void print(int x){
        static int buf[30],cnt;
        if(x == 0) return print('0');
        if(x < 0) print('-'),x = -x;
        for(cnt = 0;x;x/=10) buf[++cnt] = x%10+48;
        while(cnt) print(char(buf[cnt--])); 
    }
    inline void flush(){
        fwrite(obuf,1,ooh-obuf,stdout);
    }
}using namespace fast_IO;

int t;

const int MAXN = 200010;

struct Edge{
    int to,len,next;
}edge[MAXN];

int fir[MAXN],n,m,cnt;

void init(){
    memset(fir,0,sizeof(fir));
    cnt = 1;
}

void addedge(int from,int to,int len){
    int nown = cnt++;
    edge[nown].to = to;
    edge[nown].len = len;
    edge[nown].next = fir[from];
    fir[from] = nown;
}

int dis[MAXN];
bool vis[MAXN],flag;

void dfs(int nown){
    if(flag) return;
    vis[nown] = 1;
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].next){
        if(flag) return;
        int t = edge[nowe].to;
        if(dis[nown] + edge[nowe].len < dis[t]){
            dis[t] = dis[nown]+edge[nowe].len;
            if(vis[t]){
                flag = 1;
                return;
            }
            dfs(t);
        }
    }
    vis[nown] = 0;
}

bool spfa(){
    for(int i = 1;i<=n;i++){
        //memset(dis,0,sizeof(dis));
        flag = false;
        //dis[i] = 0;
        dfs(i);
        if(flag) return true;
    }
    return false;
}

int main(){
    freopen("1.in","r",stdin);
    read(t);
    for(int i = 1;i<=t;i++){
        init();
        read(n),read(m);
        for(int i = 1;i<=m;i++){
            int a,b,c;
            read(a),read(b),read(c);
            addedge(a,b,c);
            if(c>=0) addedge(b,a,c);
        }
        if(spfa())
            print('Y'),print('E'),print('5');
        else
            print('N'),print('0');
        print('\n');
    }
    flush();
    return 0;
}