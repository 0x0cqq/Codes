#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cctype>
using namespace std;

namespace fast_io {
    inline char read();
    inline void read(int&);
    inline void read(char*);
    inline void print(char);
    inline void print(int);
    inline void print(char*);
    inline void flush();
    inline char read() {
    //	return getchar();
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
            x = (x << 1) + (x << 3) + (c ^ '0');
        if (iosig) x = -x;
    }
    
    inline void read(char *a){
        static char c = read();
        while(c!= -1 &&(c == ' '||c =='\n'))
            c = read();
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
}using namespace fast_io;

namespace normal_io{
    inline char read(){
        return getchar();
    }
    inline void read(char *c){
    	scanf("%s",c);
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
}//using namespace normal_io;

struct treap{
    struct node{
        int val,p,cnt;
        node* son[2];
    };
    const static int MAXN = 1000000;
    int treapcnt;
    node pool[MAXN],*null,*root;
    treap(){
        treapcnt = 0;
        newnode(null);
        srand(19260817);
        null->val = -0x3f3f3f3f;
        null->p = 2147483647;
        null->cnt = 0;
        root = null;
    }
    void rotate(node *&r,int tmp){
        node *t = r->son[1-tmp];
        r->son[1-tmp] = t->son[tmp];
        t->son[tmp] = r;
        r = t;
    }
    void newnode(node *&r){
        r = &pool[treapcnt++];
        r->son[0] = r->son[1] = null;
    }
    void __insert(node *&r,int v){
        if(r == null){
            newnode(r);
            r->val = v;r->p = rand();r->cnt = 1;
        }
        else{
            if(r->val == v)
                r->cnt++;
            else{
                int tmp = v > r->val;
                __insert(r->son[tmp],v);
                if(r->son[tmp]->p < r->p)
                    rotate(r,1-tmp);
            }
        }
    }
    node *find(node *r,int t){
        while(r->son[t]!=null)
            r = r->son[t];
        return r;
    }
    void __erase(node *&r,int v){
        if(r->val == v){
            if(r->cnt > 1)
                r->cnt--;
            else{
                if(r->son[0] == null&&r->son[1] == null){
                    r = null;return;
                }
                else{
                    int tt = r->son[0]->p > r->son[1]->p;
                    rotate(r,1-tt);
                    __erase(r,v);
                }
            }
        }
        else{
            int tmp = v > r->val;
            __erase(r->son[tmp],v);
        }
    }
    node *nei(int v,int t){
        node* nown = root,*last = null;
        while(nown!=null&&nown->val!=v){
            //printf("2\n");
            int tmp = v > nown->val;
            if(tmp!=t) last = nown;
            nown = nown->son[tmp];
        }
        if(nown->son[t]!=null){
            last = find(nown->son[t],1-t);
        }
        return last;
    }
    bool find(int v){
        node *r = root;
        while(r!=null&&r->val!=v){
            int tmp = v > r->val;
            r = r->son[tmp];
        }
        return r != null;
    }
    inline void __print(node *r,int depth = 0){
    	if(r == null) return;
    	else{
        	__print(r->son[0],depth+1);
        	for(int i = 0;i<depth;i++) putchar(' ');
        	printf("val:%d cnt:%d P:%d son?:%d %d\n",r->val,r->cnt,r->p,r->son[0]!=null,r->son[1]!=null);
        	__print(r->son[1],depth+1);
    	}
    }
    void insert(int v){
        __insert(root,v);
    }
    void erase(int v){
        __erase(root,v);
    }
    void print(){
        __print(root);
    }
};

treap a,b;
const int MAXN = 1000000;

int head[MAXN],tail[MAXN],minn,n,m;

void init(){
    minn = 0x3f3f3f3f;
    read(n),read(m);
    static int tmp[MAXN];
    for(int i = 1;i<=n;i++){
        int t;read(t);
        a.insert(t);
        head[i] = tail[i] = tmp[i] = t;
    }
    sort(tmp+1,tmp+n+1);
    for(int i = 2;i<=n;i++){
        b.insert(abs(head[i]-head[i-1]));
        minn = min(minn,tmp[i]-tmp[i-1]);
    }
}

void solve(){
    char op[20];int x,y;
    for(int i = 1;i<=m;i++){
        read(op);
        if(op[4] == 'G')
            print(b.find(b.root,0)->val),print('\n');
        else if(op[4] == 'S')
            print(minn),print('\n');
        else if(op[4] == 'R'){
            read(x),read(y);
            if(x != n){
                b.erase(abs(head[x+1]-tail[x]));
                b.insert(abs(head[x+1]-y));
            }
            b.insert(abs(tail[x]-y));
            tail[x] = y;
            if(a.find(y)) minn = 0;
            else{
                int low = a.nei(y,0)->val,up = a.nei(y,1)->val;
                minn = min(minn,min(abs(y-low),abs(up-y)));
            }
            a.insert(y);
        }
        else if(op[4] =='P'){
            a.print();
            printf("------------------------\n");
            b.print();
        }
        //printf("Finish\n");
    }
    
}

int main(){
    init();
    solve();
    flush();
    return 0;
}