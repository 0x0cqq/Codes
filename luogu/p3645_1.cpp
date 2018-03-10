// luogu-judger-enable-o2
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstring>
#include <bitset>
#include <cctype>
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

const int MAXN = 30000;

const int T = 1250;

const int N = 10;

int fir[MAXN*T],to[MAXN*T],len[MAXN*T],nex[MAXN*T],cnt = 1;

bitset<N+10>rrr[MAXN];

int dis[MAXN];
bool instack[MAXN];

int n,m;
bool is_doge[MAXN];

int from[MAXN],p[MAXN];

void addedge(int a,int b,int c){
    to[cnt] = b;
    len[cnt] = c;
    nex[cnt] = fir[a];
    fir[a] = cnt;
    cnt++;
}

void init(){
    read(n),read(m);
    int a,b;
    for(int i = 0;i<=m-1;i++){
        read(a),read(b);
        from[i] = a,p[i] = b;
        is_doge[a] = 1; 
        if(b<=N)
            rrr[a][b] = 1;
    }
}

void build(){
    for(int i = 0;i<m;i++){
    	if(p[i]<=N)
    		continue;
        for(int w = from[i]%p[i],j=(w-from[i])/p[i];w<n;w+=p[i],j++){
            if(w == from[i]) continue;
            if(is_doge[w]){
                addedge(from[i],w,j>0?j:-j);
            }
        }
    }
}

/*
void _print(){
    for(int i = 0;i<n;i++){
        printf("%d:\n",i);
        for(int j = 0;j<edge[i].size();j++){
            printf("    to:%d len:%d\n",edge[i][j].to,edge[i][j].len);
        }
    }
}
*/

void spfa(){
    memset(dis,0x3f,sizeof(dis));
    memset(instack,0,sizeof(instack));
    queue<int> q;
    dis[from[0]] = 0;
    q.push(from[0]);
    while(!q.empty()){
        int nown = q.front();q.pop();
        instack[nown] = 0;
        for(int nowe = fir[nown];nowe;nowe = nex[nowe]){
            int t = to[nowe],l = len[nowe];
            if(dis[t] > dis[nown]+l){
                dis[t] = dis[nown] +l;
                if(!instack[t]){
                    q.push(t);
                    instack[t] = 1;
                }
            }
        }
        
        for(int i = 1;i<=N;i++){
            if(!rrr[nown][i]) continue;
            else{
                for(int j=-(nown/i);nown+i*j<n;j++){
                    int to = nown+i*j;
                    //printf("to:%d\n",to);
                    if(to == nown) continue;
                    if(is_doge[to]){
                        if(dis[to] > dis[nown]+abs(j)){
                            dis[to] = dis[nown] + abs(j);
                            if(!instack[to]){
                                q.push(to);
                                instack[to] = 1;
                            }
                        }
                    }
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
    flush();
    return 0;
}