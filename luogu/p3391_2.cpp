#include <bits/stdc++.h>
using namespace std;

const int MAXN = 510000;
const int MAX = 2147483647;

namespace fast_IO {
    inline char read() {
//		return getchar();
        static const int IN_LEN = 1000000;
        static char buf[IN_LEN], *s, *t;
        return s==t?t=(s=buf)+fread(buf,1,IN_LEN,stdin),*s++:*s++;
    }
    inline void read(int &x) {
        static bool iosig;
        static char c;
        for (iosig = false, c = read(); !isdigit(c); c = read()) {
            if (c == '-') iosig = true;
            if (c == -1) return;
        }
        for (x = 0; isdigit(c); c = read())
            x = (x << 1) + (x << 3) + (c ^ '0');
        if (iosig) x = -x;
    }
    const int OUT_LEN = 10000000;
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
    inline void flush() {
        fwrite(obuf, 1, ooh - obuf, stdout);
    }
}using namespace fast_IO;


int k,n;

struct node_t{
    int val,p,size;
    bool rev;
    node_t *son[2],**null;
    void pushdown(){
        if(this == *null) return;
        if(rev) {
            son[0]->reverse(),son[1]->reverse();
            rev = 0;
        }
    }
    void pushup(){
        if(this == *null) return;
        size = son[0]->size + son[1]->size + 1;
    }
    void reverse(){
        if(this == *null) return;
        swap(son[0],son[1]);
        rev^=1;
    }
};


struct fhqtreap{
    node_t pool[MAXN],*tmp[MAXN],*stack[MAXN];
    node_t *root,*null;
    int cnt,tot;
    void newnode(node_t *&r,int val = 0){
        r = &pool[cnt++];
        r->val = val;r->size = 1;
        r->son[0] = r->son[1] = null;r->rev = 0;
        r->null = &null;
        r->p = rand();
    }
    fhqtreap(){
        cnt = 0;
        srand(time(NULL));
        newnode(null);
        null->p = MAX;
        root = null;
        null->size = 0;
    }
    void read_tree(int n){
        for(int i = 1;i<=n;i++)
            newnode(tmp[i],i);
    }
    node_t *build(int n){
        read_tree(n);
        int top = 1;
        newnode(stack[0],-MAX);
        stack[0]->p = -MAX;
        for(int i = 1;i<=n;i++){
            int nowp = top - 1;
            node_t *r = tmp[i],*pre = null;
            while(stack[nowp]->p > r -> p){
                stack[nowp]->pushup();
                pre = stack[nowp];
                stack[nowp] = null;
                nowp--;
            }
            stack[nowp+1] = stack[nowp]->son[1] = r;
            stack[nowp+1]->son[0] = pre;
            top = nowp+2;
        }
        while(top) stack[--top]->pushup();
        return stack[0]->son[1];
    }
    void split(node_t *r,int lsize,node_t *&ls,node_t *&rs){
        if(r == null){
            ls = null;rs = null;
            return;
        }
        r->pushdown();
        if(r->son[0]->size + 1 <= lsize){
            ls = r;
            split(r->son[1],lsize - r->son[0]->size - 1,ls->son[1],rs);
        }
        else{
            rs = r;
            split(r->son[0],lsize,ls,rs->son[0]);
        }
        ls->pushup();rs->pushup();
    }
    node_t *merge(node_t *ls,node_t *rs){
        if(ls == null) return rs;
        if(rs == null) return ls;
        if(ls->p < rs->p){
            ls->pushdown();
            ls->son[1] = merge(ls->son[1],rs);
            ls->pushup();
            return ls;
        }
        else{
            rs->pushdown();
            rs->son[0] = merge(ls,rs->son[0]);
            rs->pushup();
            return rs;
        }
    }
    void split(int ls,int ms,node_t *&l,node_t *&m,node_t *&r){
        node_t *m1;
        split(root,ls,l,m1);
        split(m1,ms,m,r);
    }
    void reverse(int lb,int rb){
        node_t *l,*m,*r;
        split(lb-1,rb-lb+1,l,m,r);
        m->reverse();  
        root = merge(l,merge(m,r));
    }
    void output(node_t *r,int *a){
        if(r == null) return;
        r->pushdown();
        output(r->son[0],a);
        a[r->son[0]->size] = r->val;
        output(r->son[1],a + r->son[0]->size+1);
    }
    void print(node_t *r = NULL,int depth = 0){
        if(r == NULL) r = root;
        if(r == null) return;
        print(r->son[0],depth+1);
        
        for(int i = 0;i<depth;i++) putchar(' ');
        printf("val:%d p:%d size:%d son:%d %d ",r->val,r->p,r->size,r->son[0] != null,r->son[1] != null);
        printf("rev?:%d\n",r->rev);        
        
        print(r->son[1],depth+1);
        return;
    }
};

fhqtreap w;

int ans[MAXN];

void init(){
    read(n),read(k);
    w.root = w.build(n);
}

void solve(){
    int a,b;
    for(int i = 1;i<=k;i++){
        read(a),read(b);
        w.reverse(a,b);
    }
    w.output(w.root,ans);
    for(int i = 0;i<n;i++){
        print(ans[i]);print(' ');
    }
    print('\n');
}

int main(){
    init();
    solve();
    flush();
    return 0;
}