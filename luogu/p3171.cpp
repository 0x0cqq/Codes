#include <cstdio>
#include <queue>
#include <cstring>
#include <cctype>
#define int long long
using namespace std;

namespace fast_io {
    inline char read() {static const int IN_LEN = 1000000;static char buf[IN_LEN], *s, *t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++) : *s++;}
    inline void read(int &x) {static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-') iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!= -1&&(c==' '||c =='\n'))c=read();while(c!=-1&&c!=' '&&c!='\n') *a++ = c,c = read();*a = 0;}
    const int OUT_LEN=1000000;char obuf[OUT_LEN],*ooh=obuf;
    inline void print(char c){if(ooh==obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;*ooh++ = c;}
    inline void print(int x) {static int buf[30], cnt;if (x == 0)print('0');else{if(x<0) print('-'),x=-x;for(cnt=0;x;x/=10) buf[++cnt] = x%10+48;while (cnt) print((char)buf[cnt--]);}}
    inline void print(char *a){while(*a) print(*a++);}
    inline void flush(){fwrite(obuf,1,ooh-obuf,stdout);}
}using namespace fast_io;

const int MAXN = 2000,MAXM = 600000;

struct Edge{
    int from,to;
    int cap,flow;
    int len,nex;
    Edge(int a,int b,int c,int l,int ne):from(a),to(b),cap(c),flow(0),len(l),nex(ne){};
    Edge(){};
}edge[MAXM];

queue<int> q;

vector<Edge> e[MAXN];

int n,m,ecnt = 2,s,t;
int dis[MAXN],fir[MAXN],cur[MAXN];

int instack[MAXN];

void addedge(int a,int b,int c){
    edge[ecnt] = Edge(a,b,c,0,fir[a]);
    fir[a] = ecnt++;
    edge[ecnt] = Edge(b,a,0,0,fir[b]);
    fir[b] = ecnt++;
}

void spfa(){
    memset(dis,0x3f,sizeof(dis));
    memset(instack,0,sizeof(instack));
    while(!q.empty()) q.pop();
    dis[1] = 0;q.push(1);
    while(!q.empty()){
        int nown = q.front();q.pop();
        instack[nown] = 0;
        for(int i = 0;i<e[nown].size();i++){
            int v = e[nown][i].to,l = e[nown][i].len;
            if(dis[v] > dis[nown] + l){
                dis[v] = dis[nown] + l;
                if(instack[v] == 0){
                    instack[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    q.push(n);
    while(!q.empty()){
        int nown = q.front();q.pop();
        for(int i = 0;i<e[nown].size();i++){
            int u = e[nown][i].from,v = e[nown][i].to;
            if(dis[v]+ e[nown][i].len == dis[u]){
                addedge(2*v,2*u-1,0x3f3f3f3f3f3f3f);
                addedge(2*u,2*v-1,0x3f3f3f3f3f3f3f);
                q.push(v);
            }
        }
    }
}

bool bfs(){
    while(!q.empty()) q.pop();
    memset(dis,0,sizeof(dis));
    memcpy(cur,fir,sizeof(fir));
    q.push(s);dis[s] = 1;
    while(!q.empty()){
        int nown = q.front();q.pop();
        for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
            int v = edge[nowe].to;
            if(dis[v] == 0 && edge[nowe].cap > edge[nowe].flow){
                dis[v] = dis[nown]+1;
                q.push(v);
            }
            if(v == t)
                return true;
        }
    }
    return false;
}


int dfs(int nown,int limit = 0x3f3f3f3f3f3f3f3f){
    if(nown == t || limit == 0)
        return limit;
    for(int &nowe = cur[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to;
        if(dis[v] == dis[nown]+1 && edge[nowe].cap > edge[nowe].flow){
            int f = dfs(v,min(limit,edge[nowe].cap-edge[nowe].flow));
            if(f > 0){
                edge[nowe].flow += f;
                edge[nowe^1].flow -= f;
                return f;
            }
        }
    }
    return 0;
}

int dinic(){
    int ans = 0,f = 0;
    while(bfs())
        while((f = dfs(s)) > 0)
            ans += f;
    return ans;
}

void init(){
    read(n),read(m);
    s = 2,t = 2*n-1;
    int a,b,c;
    for(int i = 1;i<=m;i++){
        read(a),read(b),read(c);
        e[a].push_back(Edge(a,b,0x3f3f3f3f3f3f3f3f,c,0));
        e[b].push_back(Edge(b,a,0x3f3f3f3f3f3f3f3f,c,0));
    }
    for(int i = 1;i<=n;i++){
        read(c);
        addedge(2*i-1,2*i,c);
    }
}

void __print(){
    for(int i = 1;i<=2*n;i++){
        printf("%d:\n",i);
        for(int nowe = fir[i];nowe;nowe = edge[nowe].nex){
            printf("    to:%d flow:%d cap:%d len:%d\n",edge[nowe].to,edge[nowe].flow,edge[nowe].cap,edge[nowe].len);
        }
    }
}

void solve(){
    //__print();
    spfa();
    print(dinic()),print('\n');
}


main(){
    init();
    solve();
    flush();
    return 0;
}