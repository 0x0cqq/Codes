#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cctype>
using namespace std;

namespace fast_io {
    inline char read(){static const int IN_LEN=1000000;static char buf[IN_LEN],*s,*t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++) : *s++;}
    inline void read(int &x){static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-')iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!=-1&&(c==' '||c=='\n'||c=='\r'))c=read();while(c!=-1&&c!='\r'&&c!=' '&&c!='\n') *a++=c,c=read();*a=0;}
    const int OUT_LEN=1000000;char obuf[OUT_LEN],*ooh=obuf;
    inline void print(char c){if(ooh==obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;*ooh++ = c;}
    inline void print(int x){static int buf[30],cnt;if(x==0)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while (cnt) print((char)buf[cnt--]);}}
    inline void print(char *a){while(*a) print(*a++);}
    inline void flush(){fwrite(obuf,1,ooh-obuf,stdout);}
}using namespace fast_io;

const int MAXN = 110000,MAXM = 200000;

struct Edge{
    int from,to;
    int cap,flow;
    int nex;
}edge[MAXM];

int n,m,s,t,ecnt = 2;

int fir[MAXN],cur[MAXN];

void addedge(int a,int b,int c){
    edge[ecnt] = (Edge){a,b,c,0,fir[a]};
    fir[a] = ecnt++;
    edge[ecnt] = (Edge){b,a,0,0,fir[b]};
    fir[b] = ecnt++;
}

int dis[MAXN];

queue<int> q;

bool bfs(){
    memset(dis,0,sizeof(dis));
    memcpy(cur,fir,sizeof(cur));
    while(!q.empty()) q.pop();
    dis[s] = 1;q.push(s);
    while(!q.empty()){
        int nown = q.front();q.pop();
        for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
            int v = edge[nowe].to;
            if(dis[v] == 0 && edge[nowe].cap > edge[nowe].flow){
                dis[v] = dis[nown] + 1;
                q.push(v);
                if(v == t)
                    return 1;
            }
        }
    }
    return 0;
}



int dfs(int nown,int limit = 0x3f3f3f3f){
    if(nown == t || limit == 0)
        return limit;
    for(int &nowe = cur[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to;
        if(dis[v] == dis[nown] + 1 && edge[nowe].cap > edge[nowe].flow){
            int f = dfs(v,min(limit,edge[nowe].cap - edge[nowe].flow));
            if(f){
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
    int a,b;s = 2*n+1,t = 2*n+2;
    for(int i = 1;i<=m;i++){
        read(a),read(b);
        addedge(a,b+n,1);
    }
    for(int i = 1;i<=n;i++){
        addedge(s,i,1);
        addedge(i+n,t,1);
    }
}

void d(int nown){
    dis[nown] = 0x3f3f3f3f;
    print(nown),print(' ');
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to;
        if(edge[nowe].flow == 1 && dis[v-n] == 0){
            d(v-n);
            //dis[v-n] = 1;
        }
    }
}

int f[MAXN];
int find(int x){return f[x] == x?x:f[x] = find(f[x]);}

void solve(){
    int t = dinic();
    memset(dis,0,sizeof(dis));
    static int in[MAXN],out[MAXN];
    for(int i = 2;i<=ecnt;i++){
        if()
    }
    for(int i = n;i>=1;--i){
        if((in[i] == 1 && out[i] == 0) && dis[i] == 0)
            d(i),print('\n');
    }
    print(n-t),print('\n');
}

int main(){
    init();
    solve();
    flush();
    return 0;
}