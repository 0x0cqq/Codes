#include <cstdio>
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

const int MAXN = 151000;

struct Link_Cat_Tree{
    int val[MAXN],maxn[MAXN];
    int c[MAXN][2],f[MAXN];
    bool rev[MAXN];
    int getmax(int u,int x,int y){
        if(val[u] >= val[maxn[x]] && val[u] >= val[maxn[y]])
            return u;
        else if(val[maxn[x]] >= val[maxn[y]])
            return maxn[x];
        else 
            return maxn[y];
    }
    bool noroot(int x){
        return (c[f[x]][1] == x) || (c[f[x]][0] == x);
    }
    void push_up(int x){
        if(!x) return;
        maxn[x] = getmax(x,c[x][0],c[x][1]);
    }
    void reverse(int x){
        if(!x) return;
        swap(c[x][0],c[x][1]);
        rev[x]^=1;
    }
    void push_down(int x){
        if(!x) return;
        if(rev[x]){
            reverse(c[x][0]),reverse(c[x][1]);
            rev[x] = 0;
        }
    }
    void push_all(int x){
        if(!x) return;
        if(noroot(x)) push_all(f[x]);
        push_down(x);
    }
    void rotate(int x){
        int y = f[x],z = f[y],t = (c[y][1] == x),w = c[x][1-t];
        if(noroot(y)) c[z][c[z][1]==y] = x;
        c[x][1-t] = y;c[y][t] = w;
        if(w) f[w] = y;
        f[y] = x;f[x] = z;
        push_up(y),push_up(x);
    }
    void splay(int x){
        push_all(x);
        while(noroot(x)){
            int y = f[x],z = f[y];
            if(noroot(y))
                (c[z][1] == y) ^ (c[y][1] == x) ? rotate(x):rotate(y);
            rotate(x);
        }
    }
    void access(int x){
        for(int y = 0;x;x=f[y=x]){
            splay(x);
            c[x][1] = y,push_up(x);
        }
    }
    void makeroot(int x){
        access(x);splay(x);reverse(x);
    }
    int findroot(int x){
        access(x);splay(x);
        push_down(x);
        while(c[x][0])
            x = c[x][0],push_down(x);
        return x;
    }
    void link(int x,int y){
        // printf("Link:%d %d\n",x,y);
        makeroot(x);
        if(findroot(y) != x)
            f[x] = y;
        //print(5);
    }
    void cat(int x,int y){
        // printf("Cat:%d %d\n",x,y);
        makeroot(x);
        if(findroot(y) == x && f[x] == y && !c[x][1])
            f[x] = c[y][0] = 0,push_up(y);
    }
    void split(int x,int y){
        makeroot(x),access(y),splay(y);
    }
    int querymax(int x,int y){
        return split(x,y),maxn[y];
    }
    void print(int n){
        printf("-------------------\n");
        for(int i = 1;i<=n;i++){
            printf("%d: sum:%d v:%d f:%d c:%d %d r:%d\n",i,maxn[i],val[i],f[i],c[i][0],c[i][1],int(rev[i]));
        }
        printf("-------------------\n");
    }
}T;

//点1->n 边n+1->n+m
int n,m;

struct Edge{
    int from,to,a,b;
}edge[MAXN];

bool cmp(Edge x,Edge y){
    return x.a < y.a;
}

void init(){
    read(n),read(m);
    int a,b,f,t;
    for(int i = 1;i<=m;i++){
        read(f),read(t),read(a),read(b);
        edge[i] = (Edge){f,t,a,b};
    }
}

void solve(){
    int ans = 0x3f3f3f3f;
    sort(edge + 1,edge+m+1,cmp);
    // for(int i = 1;i<=m;i++){
    //     printf("Edge%d: %d %d %d %d\n",i,edge[i].from,edge[i].to,edge[i].a,edge[i].b);
    // }
    for(int i = 1;i<=m;i++)
        T.val[n+i] = edge[i].b;
    for(int i = 1;i<=n+m;i++)
        T.maxn[i] = i;
    int x = 0,y = 0,a = 0,b = 0;
    for(int i = 1;i<=m;i++){
        x = edge[i].from,y = edge[i].to;
        a = edge[i].a,b = edge[i].b;
        if(x == y) continue;
        if(T.findroot(x)!=T.findroot(y))
            T.link(n+i,x),T.link(n+i,y);
        else{
            int t = T.querymax(x,y) - n;
            //printf("%d:%d\n",i,t);
            if(edge[t].b < b) continue;
            T.cat(n+t,edge[t].from),T.cat(n+t,edge[t].to);
            T.link(n+i,x),T.link(n+i,y);
        }
        //T.print(n+m);
        if(T.findroot(1) == T.findroot(n))
            ans = min(ans,a+edge[T.querymax(1,n)-n].b);
        //printf("maxn:%d max:%d\n",T.querymax(1,n)-n,edge[T.querymax(1,n)-n].b);
        //T.print(n+m);
    }
    if(ans > 1000000000)
        print(-1);
    else
        print(ans);
    print('\n');
}

int main(){
    init();
    solve();
    flush();
    return 0;
}