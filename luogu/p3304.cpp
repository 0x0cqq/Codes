#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <cctype>
#include <algorithm>
#define int long long
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

const int MAXN = 300000;
struct Edge{
    int from,to,len;
};
int n,u=0,v=0,dis[MAXN],fa[MAXN],ans1,ans2 = 0x3f3f3f3f3f;
vector<Edge> edge[MAXN];
void addedge(int a,int b,int c){
    edge[a].push_back((Edge){a,b,c});
    edge[b].push_back((Edge){b,a,c});
}

void init(){
    read(n);
    int a,b,c;
    for(int i = 1;i<=n-1;i++){
        read(a),read(b),read(c);
        addedge(a,b,c);
    }
}


void dfs(int nown,int f){
    fa[nown] = f;
    for(int i = 0;i<edge[nown].size();i++){
        Edge e = edge[nown][i];
        if(e.to == f) continue;
        dis[e.to] = dis[nown] + e.len;
        dfs(e.to,nown);
    }
}

void find(){
    memset(dis,0,sizeof(dis));
    dfs(1,0);
    for(int i = 1;i<=n;i++){
        //printf("%d ",dis[i]);
        if(dis[i] > dis[u])
            u = i;
    }
    //printf("\n");
    memset(dis,0,sizeof(dis));
    dfs(u,0);
    for(int i = 1;i<=n;i++){
        //printf("%d ",dis[i]);
        if(dis[i] > dis[v])
            v = i,ans1 = dis[i];
    }
    //printf("\n");
}

bool dfs2(int nown,int len){
    if(len == 0) return true;
    for(int i = 0;i < edge[nown].size();i++){
        Edge e = edge[nown][i];
        if(e.to == fa[nown]) continue;
        if(dfs2(e.to,len - e.len))
            return true;
    }
    return false;
}

void solve(){
    static int nex[MAXN];
    int x = v,tmp = 0;
    while(x!=u){
        nex[fa[x]] = x;
        x = fa[x];
        tmp++;
    }
    ans2 = tmp;
    //printf("%d\n",ans2);
    int l = 0,r = tmp,nowt = 0;
    //printf("u:%lld v:%lld\n",u,v);
    for(x = u;x!=v;x = nex[x]){
        for(int i = 0;i<edge[x].size();i++){
            Edge e = edge[x][i];
            if(e.to == fa[x] || e.to == nex[x]) continue;
            if(dfs2(e.to,dis[x] - e.len)) l = max(nowt,l);
            else if(dfs2(e.to,(ans1 - dis[x])- e.len)) r = min(r,nowt);
        }
        nowt++;
        //printf("%lld %lld %lld\n",x,l,r);
    }
    //printf("l:%lld r:%lld\n",l,r);
    ans2 = r - l;
}


signed main(){
    init();
    find();
    solve();
    printf("%lld\n%lld\n",ans1,ans2);
    return 0;   
}
