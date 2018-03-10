#include <cstdio>
#include <queue>
#include <cstring>
#include <vector>
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
    inline void print(char c){
        putchar(c);
    }
    inline void flush(){
        return;
    }
}//using namespace normal_io;

struct Edge{
    int to,len;
};

const int MAXN = 30000;

vector<Edge> edge[MAXN];

int dis[MAXN];
bool instack[MAXN];

int n,m;
bool is_doge[MAXN];

int from[MAXN],p[MAXN];

void init(){
    read(n),read(m);
    int a,b;
    for(int i = 0;i<=m-1;i++){
        read(a),read(b);
        from[i] = a,p[i] = b;
        is_doge[a] = 1; 
    }
}

void build(){
    for(int i = 0;i<m;i++){
        for(int w = from[i]%p[i],j=(w-from[i])/p[i];w<n;w+=p[i],j++){
            if(w == from[i]) continue;
            if(is_doge[w]){
                Edge a;
                a.to = w,a.len = j>0?j:-j;
                edge[from[i]].push_back(a);
            }
        }
    }
}

void _print(){
    for(int i = 0;i<n;i++){
        printf("%d:\n",i);
        for(int j = 0;j<edge[i].size();j++){
            printf("    to:%d len:%d\n",edge[i][j].to,edge[i][j].len);
        }
    }
}

void spfa(){
    memset(dis,0x3f,sizeof(dis));
    memset(instack,0,sizeof(instack));
    queue<int> q;
    dis[from[0]] = 0;
    q.push(from[0]);
    while(!q.empty()){
        int nown = q.front();q.pop();
        instack[nown] = 0;
        for(int i = 0;i<edge[nown].size();i++){
            int to = edge[nown][i].to,len = edge[nown][i].len;
            if(dis[to] > dis[nown]+len){
                dis[to] = dis[nown] +len;
                if(!instack[to]){
                    q.push(to);
                    instack[to] = 1;
                }
            }
        }
    }
    if(dis[from[1]]>100000000){
        print(-1);
    }
    else{
        print(dis[from[1]]);
    }
    print('\n');
}


int main(){
    init();
    build();
    //_print();
    spfa();
    return 0;
}