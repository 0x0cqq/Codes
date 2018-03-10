#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 110000;

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
    inline void print(char x){
        putchar(x);
    }
    inline void flush(){
        return;
    }
}using namespace normal_io;

int n,m;

int fir[MAXN],to[MAXN],nex[MAXN];

int ans[MAXN],anscnt;

void addedge(int u,int v,int cnt){
    nex[cnt] = fir[u];
    fir[u] = cnt;
    to[cnt] = v;
}

void init(){
    read(n),read(m);
    memset(fir,0,sizeof(fir));
    memset(ans,0,sizeof(ans));
    //memset(tmp,0,sizeof(tmp));
    int a,b;
    for(int i = 1;i<=m;i++){
        read(a),read(b);
        addedge(b,a,i);
    }
}

bool judge(){
    static int q[MAXN],in[MAXN],cnt;
    memset(in,0,sizeof(in));
    cnt = 0;
    int tot = 0;
    for(int i = 1;i<=n;i++)
        for(int nowe = fir[i];nowe;nowe = nex[nowe])
            in[to[nowe]]++;
    for(int i = 1;i<=n;i++)
        if(in[i] == 0)
            q[cnt++] = i;
    while(cnt){
        int nown = q[--cnt];
        //printf("%d\n",nown);
        tot++;
        for(int nowe = fir[nown];nowe;nowe = nex[nowe])
            if(--in[to[nowe]] == 0)
                q[cnt++] = to[nowe];
    }
    return tot == n;
}

void solve(){
    static int heap[MAXN],tmp[MAXN],out[MAXN],heapcnt,tmpcnt;
    static bool vis[MAXN];
    static int stack[MAXN],stackcnt;
    static bool instack[MAXN];
    anscnt = 0;
    if(!judge()) {
        printf("Impossible!\n");
        return;
    }

    memset(out,0,sizeof(out));
    memset(instack,0,sizeof(instack));
    memset(vis,0,sizeof(vis));
    for(int i = 1;i<=n;i++){
        if(vis[i]) continue;

        stackcnt = 0;
        stack[stackcnt++] = i;
        while(stackcnt){
            int nown = stack[--stackcnt];
            for(int nowe = fir[nown];nowe;nowe = nex[nowe]){
                int t = to[nowe];
                if(!vis[t]) out[t]++;
                if(!vis[t]&&!instack[t]) instack[t] = 1,stack[stackcnt++] = t;
            }
        }

        heapcnt = tmpcnt = 0;
        heap[heapcnt++] = i;vis[i] = 1;
        while(heapcnt){
            int nown = tmp[tmpcnt++] = heap[0];
            pop_heap(heap,heap+(heapcnt--));
            for(int nowe = fir[nown];nowe;nowe = nex[nowe]){
                int t = to[nowe];
                if(vis[t]) continue;
                else if(--out[t]) continue;
                else{
                    heap[heapcnt++] = t;
                    vis[t] = 1;
                    make_heap(heap,heap+heapcnt);
                }
            }
        }
        for(int j = tmpcnt-1;j>=0;j--)
            ans[anscnt++] = tmp[j];
    }
    for(int i = 0;i<anscnt;i++)
        print(ans[i]),print(' ');
    print('\n');
}

int main(){
    int T;
    read(T);
    for(int i = 1;i<=T;i++){
        init();
        solve();
    }
    return 0;
}