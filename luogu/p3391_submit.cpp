#include <cstdio>
#include <algorithm>
using namespace std;

inline void qr(int &x){
    bool f = 0;char ch = getchar();
    while(ch<'0'||ch>'9')
        f = (ch == '-'),ch = getchar();
    x = 0;
    while(ch>='0'&&ch<='9')
        x = (x<<3)+(x<<1)+ch-48,ch = getchar();
    if(f) x = -x;
}

template <typename T,size_t siz>
struct splay_t{
    struct node_t{
        T val;
        int size;bool rev;
        node_t *son[2],*parent,**root,**null;
        inline void init(node_t **root,node_t **null) {this->root = root,this->null = null;}
        inline bool get_p() {return parent->son[1] == this;}
        inline void maintain() { size = son[0]->size + son[1]->size+1;}
        inline void link(node_t *dst,bool s){parent = dst;dst->son[s] = this;}
        inline void push_down() {
            if(this == *null) return;
            if(rev){
                swap(son[0],son[1]);
                son[0]->rev^=1,son[1]->rev^=1;
                rev = 0;
            }
        }
        inline void rotate(){
            parent->push_down(),push_down();
            node_t* rp = parent;bool re = get_p();
            link(rp->parent,rp->get_p());son[1-re]->link(rp,re);rp->link(this,1-re);
            rp->maintain(),maintain();
            if(parent == *null) *root = this; 
        }
        void splay(node_t *target = NULL){
            if(target == NULL) target = *null;
            while(parent!=target){
                parent->push_down();
                //printf("?%d\n",parent->parent == target);
                if(parent->parent == target){
                    rotate();
                }
                else{
                    if(get_p() == parent->get_p())
                        parent->rotate(),rotate();
                    else
                        rotate(),rotate();
                }
            }
        }
    };
    node_t *null, *root,*lb,*rb;
    int cnt;node_t pool[siz<<1];
    inline node_t* newnode(){pool[cnt].parent = pool[cnt].son[0] = pool[cnt].son[1] = null;return &pool[cnt++];}
    splay_t(){
        cnt = 0,null = newnode();
        root = null;
        null->init(&root,&null);
    }
    node_t* find(int rank){
        node_t *r = root;
        while(true){
            r->push_down();
            //printf("v:%d,%d\n",r->val,r==null);
            if(r->son[0]->size > rank)
                r = r->son[0];
            else if(r->son[0]->size == rank)
                return r;
            else
                rank -= r->son[0]->size+1,r = r->son[1];
        }
    }
    node_t* __build(T *a,int l,int r,int sl,int sr){
        if(l>r) return null;
        int mid = (l+r)>>1;
        node_t *now = newnode();
        now->init(&root,&null);
        now->val = a[mid];
        node_t *ltree = __build(a,l,mid-1,sl,sr),*rtree = __build(a,mid+1,r,sl,sr);
        ltree->link(now,0),rtree->link(now,1);
        if(l == sl && now->son[0] == null){
            lb = newnode();
            lb->init(&root,&null);
            lb->size = 1;
            lb->link(now,0);
        }
        if(r == sr && now->son[1] == null){
            rb = newnode();
            rb->init(&root,&null);rb->size = 1;
            rb->link(now,1);
        }
        now->maintain();
        return now;
    }
    node_t* select(int b,int e){
        node_t *lb = find(b-1);
        node_t *rb = find(e+1);
        lb->splay(null);
        rb->splay(lb);
        return rb->son[0];
    }
    void reverse(int b,int e){
        node_t *range = select(b,e);
        range->rev^=1;
    }
    void output(T *a,node_t *r = NULL){
        if(r == NULL) r = root;
        if(r == null) return;
        r->push_down();
        output(a,r->son[0]);
        a[r->son[0]->size] = r->val;//printf("%d ",r->val);
        output(a+r->son[0]->size+1,r->son[1]);
    }
    void build(T *a,int l,int r){
        root = __build(a,l,r,l,r);
    }
};

splay_t<int,210000> s;
int a[210000],n,m,ans[210000];


int main(){
    qr(n);qr(m);
    for(int i = 1;i<=n;i++)
        a[i] = i;
    s.build(a,1,n);
    for(int i = 0;i<m;i++){
        int x,y;
        qr(x);qr(y);
        s.reverse(x,y);
    }
    s.output(ans);
    for(int i = 1;i<=n;i++)
        printf("%d ",ans[i]);
    putchar('\n');
    return 0;
}