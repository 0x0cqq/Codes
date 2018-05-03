// luogu-judger-enable-o2
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
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

const int MAXN = 100000,MAXM = 2000000;

struct Edge{
    int from,to;
    int cap,flow;
    int cost,nex;
}edge[MAXM];

int n,m,s,t,sum = 0;
int ff = 0,cc = 0,p[MAXN],ti[1000][1000];
int fir[MAXN],ecnt = 2;

void addedge(int a,int b,int c,int d){
    //printf("%d %d %d %d\n",a,b,c,d);
    edge[ecnt] = (Edge){a,b,c,0,d,fir[a]};
    fir[a] = ecnt++;
    edge[ecnt] = (Edge){b,a,0,0,-d,fir[b]};
    fir[b] = ecnt++;
}

int dis[MAXN],instack[MAXN],pree[MAXN];
queue<int> q;

bool spfa(){
    while(!q.empty()) q.pop();
    memset(dis,0x3f,sizeof(dis));
    memset(instack,0,sizeof(instack));
    q.push(s);dis[s] = 0;
    while(!q.empty()){
        int nown = q.front();q.pop();
        instack[nown] = 0;
        for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
            Edge e = edge[nowe];
            if(dis[e.to] > dis[nown] + e.cost && e.cap > e.flow){
                dis[e.to] = dis[nown] + e.cost;
                pree[e.to] = nowe;
                if(instack[e.to] == 0){
                    q.push(e.to);
                    instack[e.to] = 1;
                }
            }
        }
    }
    return dis[t] < 0x3f3f3f3f;
}

void argument(){
    int nown = t,nowe = 0,limit = 0x3f3f3f3f;
    while(nown != s){
        nowe = pree[nown];
        limit = min(limit,edge[nowe].cap - edge[nowe].flow);
        nown = edge[nowe].from;
    }
    nown = t;
    while(nown != s){
        nowe = pree[nown];
        edge[nowe].flow += limit;
        edge[nowe^1].flow -= limit;
        nown = edge[nowe].from;
    }
    ff += limit,cc += limit * dis[t];
}


void init(){
    read(n),read(m);
    for(int i = 1;i<=n;i++){
    	read(p[i]);
    	sum += p[i];
    }
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            read(ti[i][j]);
        }
    }
}

void solve(){
    s = m*sum + n + 1,t = m*sum + n + 2;
    for(int i = 1;i<=n;i++)
        addedge(s,m*sum + i,p[i],0);
    for(int j = 1;j<=m;j++){
        addedge(j,t,1,0);
        for(int i = 1;i<=n;i++){	
            addedge(m*sum + i,j,1,ti[i][j]);
        }
    }
    while(spfa()){
        argument();
        int x = edge[pree[t]].from;
        addedge(x+m,t,1,0);
        for(int i = 1;i<=n;i++){
            //printf("%d %d:%d\n",i,(x-1)%m + 1,ti[i][(x-1)%m + 1] * (x+m-1)/m + 1);
            addedge(m*sum + i,x+m,1,ti[i][(x-1)%m + 1] * ((x+m-1)/m + 1));
        }
    }
    print(cc),print('\n');
}

int main(){
    //freopen("1.txt","r",stdin);
    init();
    solve();
    flush();
    return 0;
}