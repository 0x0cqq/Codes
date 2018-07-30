#include <cstdio>
#include <algorithm>
#include <cctype>
using namespace std;

inline char read(){
    const int SIZE = 1024*1024;
    static char *s,*t,ibuf[SIZE];
    if(s == t)
        t = (s = ibuf) + fread(ibuf,1,SIZE,stdin);
    return s == t ? -1: (*s++);
}

inline void read(int &x){
    static bool iosig = 0;char ch;
    for(ch = read(),iosig = 0;!isdigit(ch);ch= read()){
        if(ch == '-') iosig = 1;
        if(ch == -1) return;
    }
    for(x = 0;isdigit(ch);ch = read())
        x = (((x<<2)+x)<<1) + (ch^48);
    if(iosig) x = -x;
}

const int MAXN = 13000;

struct Link_Cat_Tree{
    int v[MAXN],maxn[MAXN];
    int f[MAXN],c[MAXN][2];
    bool rev[MAXN];
    void push_up(int x){
        maxn[x] = max(max(maxn[c[x][0]],maxn[c[x][1]]),v[x]);
    }
    void reverse(int x){
        swap(c[x][0],c[x][1]);
        rev[x] ^= 1;
    }
    void push_down(int x){
        if(rev[x]){
            reverse(c[x][0]),reverse(c[x][1]);
            rev[x] = 0;
        }
    }
    bool noroot(int x){
        return c[f[x]][0] == x || c[f[x]][1] == x;
    }
    void push_all(int x){
        if(noroot(x))
            push_all(f[x]);
        push_down(x);
    }
    void rotate(int x){
        int y = f[x],z = f[y],t = (c[y][1] == x),w = c[x][1-t];
        if(noroot(y)) c[z][c[z][1]==y] = x;
        c[y][t] = w,c[x][1-t] = y;
        if(w) f[w] = y;
        f[x] = z,f[y] = x;
        push_up(y),push_up(x);
    }
    void splay(int x){
        push_all(x);
        while(noroot(x)){
            int y = f[x],z = f[y];
            if(noroot(y)){
                if((c[y][1]==x)^(c[z][1]==y))
                    rotate(x);
                else rotate(y);
            }rotate(x);
        }
    }
    void access(int x){
        for(int y = 0;x;x = f[y = x]){
            splay(x);c[x][1] = y;
            push_up(x);
        }
    }
    void makeroot(int x){
        access(x),splay(x),reverse(x);
    }
    void split(int x,int y){//split后y位于树根（代表整条链
        makeroot(x),access(y),splay(y);
    }
    int find(int x){
        access(x),splay(x);
        push_down(x);
        while(c[x][0]){
            x = c[x][0],push_down(x);
        }
        return x;
    }
    bool link(int x,int y){
        makeroot(x);
        if(find(y) != x){
            f[x] = y;
            return 1;
        }else return 0;
    }
    bool judge(int x,int y){
        makeroot(x);
        return find(y) == x && f[x] == y && !c[x][1];
    }
    bool cat(int x,int y){
        makeroot(x);//find 之后 y 位于 树根
        if(find(y) == x && f[x] == y && !c[x][1]){
            f[x] = c[y][0] = 0;push_up(y);
            return 1;
        }else return 0;
    }
    void update(int x,int val){
        makeroot(x);
        v[x] = val,push_up(x);
    }
    int query(int x,int y){
        makeroot(x);
        if(find(y)!=x)
            return -1;
        else{
            access(y),splay(y);
            return maxn[y];
        }
    }
}T[10];// Tree 0 -> 9
int d[MAXN][10];// degree 

int n,m,c,k;

void update(int x,int v){
    for(int i = 0;i<c;i++)
        T[i].update(x,v);
}

int change(int u,int v,int w){
    if(T[w].judge(u,v)) return 0;
    for(int i = 0;i<c;i++){
        if(T[i].judge(u,v)){
            if(d[u][w] >= 2 || d[v][w] >= 2)
                return 1;
            else{
                if(!T[w].link(u,v))
                    return 2;
                else{
                    d[u][i]--,d[v][i]--;
                    T[i].cat(u,v);
                    d[u][w]++,d[v][w]++;
                    return 0;
                }
            }
        }
    }
    return -1;
}

void init(){
    read(n),read(m),read(c),read(k);
    int u,v,w;
    for(int i = 1;i<=n;i++){
        read(v);
        update(i,v);
    }
    for(int i = 1;i<=m;i++){
        read(u),read(v),read(w);
        T[w].link(u,v);
        d[u][w]++,d[v][w]++;
    }
}

int query(int u,int v,int w){
    return T[w].query(u,v);
}

void solve(){
    int op,u,v,w;
    for(int i = 1;i<=k;i++){
        read(op);
        if(op == 0){
            read(u),read(v);
            update(u,v);
        }
        else if(op == 1){
            read(u),read(v),read(w);
            int t = change(u,v,w);
            if(t>0) printf("Error %d.\n",t);
            else if(t==-1) printf("No such edge.\n");
            else printf("Success.\n");
        }
        else if(op == 2){
            read(w),read(u),read(v);
            printf("%d\n",query(u,v,w));
        }
    }
}

int main(){
    init();
    solve();
    return 0;
}