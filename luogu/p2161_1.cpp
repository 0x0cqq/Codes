#include <cstdio>
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

template<int MAXN>
struct Splay{
    struct node_t{
        int v[2];
        int siz;
        node_t *son[2],**null,**root,*p;
        void init(node_t **root,node_t **null){
            this->root = root,this->null = null;
        }
        bool get_p(){
            return p->son[1] == this;
        }
        node_t* link(node_t *dst,int s){
            dst->son[s] = this;
            this->p = dst;
            return this;
        }
        void maintain(){
            if(this == *null) return;
            siz = son[0]->siz + son[1]->siz+1;
        }
        void rotate(){
            node_t *rp = p;bool re = get_p();
            link(rp->p,rp->get_p());
            son[1-re]->link(rp,re);
            rp->link(this,1-re);
            rp->maintain(),maintain();
            if(p == *null) *root = this;
        }
        node_t *splay(node_t *tar = NULL){
            if(tar == NULL) tar = *null;
            while(p!=tar){
                if(p->p == tar)
                    rotate();
                else{
                    if(get_p()==p->get_p())
                        p->rotate(),rotate();
                    else
                        rotate(),rotate();
                }
            }
            return this;
        }
    };
    node_t pool[MAXN],*null,*root;
    int cnt;
    void newnode(node_t *&r){
        r = &pool[cnt++];
        r->son[0] = r->son[1] = r-> p = null; 
        r->siz = 0;
        r->init(&root,&null);
    }
    Splay(){
        cnt = 0;
        newnode(null);
        node_t *lb,*rb;newnode(lb),newnode(rb);
        root = lb;
        lb->v[0] = lb->v[1] = -1,rb->v[0] = rb->v[1] = 0x3f3f3f3f;
        rb->link(lb,1)->maintain();
        lb->maintain();
    }
    node_t* find(int rank){//rank就是有多少个数比这个小
        node_t *r = root;
        while(true){
            if(rank < r->son[0]->siz)
                r = r->son[0];
            else if(rank == r->son[0]->siz)
                return r->splay();
            else
                rank-= r->son[0]->siz+1,r = r->son[1];
        }
    }
    int get_rank(int val,int side){//0是左，1是右边
        node_t *r = root;int ans = 0;
        while(r!=null){
            if(val < r->v[side]){
                r = r->son[0];
            }
            else if(val == r->v[side]){
                ans += r->son[0]->siz;
                break;
            }
            else{
                ans += r->son[0]->siz+1;
                r = r->son[1];
            }
        }
        if(r!=null) r->splay();
        return ans;
    }
    int insert(int l,int r){
        node_t *lb = find(get_rank(l,1)-1),
                *rb = find(get_rank(r+1,0));
        node_t *newn;newnode(newn);
        newn->v[0] = l,newn->v[1] = r;
        lb->splay();rb->splay(lb);
        int ans = rb->son[0]->siz;
        newn->link(rb,0)->maintain();
        rb->maintain();lb->maintain();
        return ans;
    }
    int get_size(){
        return root->siz - 2;
    }
};

Splay<300000> t;

int n;

void solve(){
    read(n);
    char op[20];int l,r;
    for(int i = 1;i<=n;i++){
        read(op);
        if(op[0] == 'A'){
            read(l),read(r);
            print(t.insert(l,r)),print('\n');
        }
        else if(op[0] == 'B'){
            print(t.get_size()),print('\n');
        }
    }
}

int main(){
    solve();
    flush();
    return 0;
}