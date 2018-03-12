#include <cstdio>
#include <vector>
#include <cctype>
#include <unistd.h>
#define lson (nown<<1)
#define rson (nown<<1|1)
#define mid ((l+r)>>1)
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
    }
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
}//using namespace fast_io;

namespace normal_io{
    char read(){
        return getchar();
    }
    void read(int &x){
        scanf("%d",&x);
    }
    void read(char *x){
        scanf("%s",x);
    }
    void print(int x){
        printf("%d",x);
    }
    void print(char c){
        putchar(c);
    }
    void flush(){
        return;
    }
}using namespace normal_io;

const int MAXN = 110000;

int n,m;
int son[MAXN],top[MAXN],fa[MAXN],siz[MAXN],dep[MAXN];
int id[MAXN],id_to[MAXN],num[MAXN],cnt = 1;

vector<int> edge[MAXN];

struct node{
    int num,lcol,rcol;
    bool lazy;
    node(int n = 0,int l = 0,int r = 0):num(n),lcol(l),rcol(r){};
    bool empty(){
        return num == 0;
    }
}pool[MAXN<<2];

inline node merge(node l,node r){
    if(l.empty()) return r;
    if(r.empty()) return l;
    node ans;
    ans.num = l.num+r.num;
    if(l.rcol == r.lcol)
        ans.num-=1;
    ans.lcol = l.lcol,ans.rcol = r.rcol;
    return ans;
}

inline void push_down(int nown,int l,int r){
    if(pool[nown].lazy){
        int c = pool[nown].lcol;
        pool[lson] = node(1,c,c),pool[lson].lazy = 1;
        pool[rson] = node(1,c,c),pool[lson].lazy = 1;
        pool[nown].lazy = 0;
    }
}

inline node reverse(node nown){
    swap(nown.lcol,nown.rcol);
    return nown;
}

inline void build(int nown,int l,int r){
    pool[nown].lazy = 0;
    if(l == r){
        pool[nown] = node(1,num[id_to[l]],num[id_to[l]]);
    }
    else{
        build(lson,l,mid);
        build(rson,mid+1,r);
        pool[nown] = merge(pool[lson],pool[rson]);
    }
}

inline void update(int nown,int l,int r,int ql,int qr,int c){
    if(ql<=l&&r<=qr){
        pool[nown] = node(1,c,c);
        pool[nown].lazy = 1;
    }
    else{
        push_down(nown,l,r);
        if(ql<=mid) update(lson,l,mid,ql,qr,c);
        if(qr>=mid+1) update(rson,mid+1,r,ql,qr,c);
        pool[nown] = merge(pool[lson],pool[rson]);
    }
}

inline node query(int nown,int l,int r,int ql,int qr){
    //printf("%d %d %d %d %d\n",nown,l,r,ql,qr);
    //usleep(100000);
    if(ql<=l&&r<=qr){
        return pool[nown];
    }
    else{
        push_down(nown,l,r);
        if(ql<=mid && mid+1<=qr){
            node ls,rs;
            ls = query(lson,l,mid,ql,qr);
            rs = query(rson,mid+1,r,ql,qr);
            return merge(ls,rs);
        }
        else if(qr<=mid){
            return query(lson,l,mid,ql,qr);
        }
        else if(ql>=mid+1){
            return query(rson,mid+1,r,ql,qr);
        }
        printf("!!!\n");
    }
}

inline void dfs1(int nown,int f,int depth){
    dep[nown] = depth,fa[nown] = f,siz[nown] = 1;
    son[nown] = 0;int maxsum = -1;
    for(int i = 0;i<edge[nown].size();i++){
        int to = edge[nown][i];
        if(to == f) continue;
        dfs1(to,nown,depth+1);
        siz[nown]+=siz[to];
        if(siz[to]>maxsum) maxsum = siz[to],son[nown] = to;
    }
}

inline void dfs2(int nown,int topf){
    top[nown] = topf,id[nown] = cnt,id_to[cnt] = nown;cnt++;
    if(!son[nown]) return;
    dfs2(son[nown],topf);
    for(int i = 0;i<edge[nown].size();i++){
        int to = edge[nown][i];
        if(to == fa[nown]||to == son[nown]) continue;
        dfs2(to,to);
    }
}

void update_range(int x,int y,int c){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        update(1,1,n,id[top[x]],id[x],c);
        x = fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    update(1,1,n,id[x],id[y],c);
}

int query_range(int x,int y){
    node lans = node(0,0,0),rans = node(0,0,0);
    while(top[x]!=top[y]){
        if(dep[top[x]] > dep[top[y]]){
            lans = merge(lans,reverse(query(1,1,n,id[top[x]],id[x])));
            x = fa[top[x]];
        }
        else{
            rans = merge(query(1,1,n,id[top[y]],id[y]),rans);
            y = fa[top[y]];
        }
    }
    if(dep[x]<dep[y]){
        lans = merge(lans,query(1,1,n,id[x],id[y]));
    }
    else{
        rans = merge(reverse(query(1,1,n,id[y],id[x])),rans);
    }
    return merge(lans,rans).num;
}

inline void init(){
    read(n),read(m);
    for(int i = 1;i<=n;i++)
        read(num[i]);
    int a,b;
    for(int i = 1;i<=n-1;i++){
        read(a),read(b);
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    dfs1(1,0,1);
    dfs2(1,1);
    build(1,1,n);
}

inline void __print(){
    for(int i = 1;i<=n;i++){
        printf("%d: id:%d son:%d fa:%d topf:%d siz:%d dep:%d\n",i,id[i],son[i],fa[i],top[i],siz[i],dep[i]);
    }
}

inline void print_tree(int nown,int l,int r,int dep = 0){
    for(int i = 0;i<dep;i++)
        putchar(' ');
    printf("%d: l:%d r:%d num:%d lcol:%d rcol:%d\n",nown,l,r,pool[nown].num,pool[nown].lcol,pool[nown].rcol);
    if(l != r){
        print_tree(lson,l,mid,dep+1);
        print_tree(rson,mid+1,r,dep+1);
    }
}

void solve(){
    char op[20];int a,b,c;
    for(int i = 1;i<=m;i++){
        read(op),read(a),read(b);
        if(op[0] == 'C'){
            read(c),update_range(a,b,c);
        }
        else if(op[0] == 'Q'){
            print(query_range(a,b)),print('\n');
        }
        //print_tree(1,1,n);
    }
}


int main(){
    init();
    //__print();
    solve();
    flush();
    return 0;
}