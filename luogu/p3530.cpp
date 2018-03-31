#include <cstdio>
#include <algorithm>
#include <cctype>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;

namespace fast_io {
    inline char read() {static const int IN_LEN = 1000000;static char buf[IN_LEN], *s, *t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++) : *s++;}
    inline void read(int &x) {static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-') iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!= -1&&(c==' '||c =='\n'))c=read();while(c!=-1&&c!=' '&&c!='\n') *a++ = c,c = read();*a = 0;}
}using namespace fast_io;

const int MAXN = 1000;

int n,m1,m2,dis[MAXN][MAXN];
int dfn[MAXN],low[MAXN],cnt = 0,instack[MAXN],col[MAXN],cnum = 0;
stack<int> a;

vector<int> edge[MAXN];


void dfs(int nown){
    dfn[nown] = low[nown] = ++cnt;
    instack[nown] = 1,a.push(nown);
    for(int i = 0;i<edge[nown].size();i++){
        int to = edge[nown][i];
        if(dfn[to] == 0)
            dfs(to),low[nown] = min(low[nown],low[to]);
        else if(instack[to])
            low[nown] = min(low[nown],dfn[to]);
    }
    if(dfn[nown]==low[nown]){
        int j = -1;cnum++;
        do{
            j = a.top();a.pop();
            instack[j] = 0;
            col[j] = cnum;
        }while(j!=nown);
    }
}

void tarjan(){
    for(int i = 1;i<=n;i++)
        if(dfn[i] == 0)
            dfs(i);
}

void init(){
    read(n),read(m1),read(m2);
    int a,b;
    for(int i = 1;i<=n;i++){
    	for(int j = 1;j<=n;j++){
    		dis[i][j] = 1000000;
    		if(i == j) dis[i][j] = 0;
    	}
    }
    for(int i = 1;i<=m1;i++){
        read(a),read(b);
        edge[a].push_back(b);
        edge[b].push_back(a);
        dis[a][b] = min(dis[a][b],1);
        dis[b][a] = min(dis[b][a],-1);
    }
    for(int i = 1;i<=m2;i++){
        read(a),read(b);
        edge[b].push_back(a);
        dis[b][a] = min(dis[b][a],0);
    }
}

void solve(){
    tarjan();
    int ans = 0;
    for(int c = 1;c<=cnum;c++){
        int res = 0;
        for(int k = 1;k<=n;k++) if(col[k] == c)
            for(int i = 1;i<=n;i++) if(col[i] == c && dis[i][k]<=100000)
                for(int j = 1;j<=n;j++) if(col[j] == c && dis[k][j]<=100000)
                    dis[i][j] = min(dis[i][k]+dis[k][j],dis[i][j]);
        for(int i = 1;i<=n;i++) if(col[i] == c)
            for(int j = 1;j<=n;j++) if(col[j] == c)
                res = max(res,dis[i][j]);
        ans+=res+1;
    }
    for(int i = 1;i<=n;i++){
        if(dis[i][i] < 0)
            return void(printf("NIE\n"));
    }
    printf("%d\n",ans);
}

int main(){
    init();
    solve();
    return 0;
}