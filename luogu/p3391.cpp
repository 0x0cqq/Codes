#include <cstdio>
#include <algorithm>
using namespace std;


template <typename T,size_t siz>
struct splay_t{
    struct node_t{
        T val;
        int size;bool rev;
        node_t *son[2],*parent;
    };
    node_t *null,*root;
    int cnt;node_t pool[siz<<1];
    splay_t(){
        cnt = 0;
        null = newnode();null->size = 0;
        root = null;
    }
    node_t* newnode(T v = 0){
        node_t *r = &pool[cnt++];
        r->val = v;
        r->size = 1;
        r->rev = 0;
        r->parent = r->son[0] = r->son[1] = null;
        return r;   
    }
    inline bool get_p(node_t *r){return r->parent->son[1] == r;}
    void maintain(node_t *r){
        r->size = r->son[0]->size+r->son[1]->size+1;
    }
    void link(node_t *r,node_t *dst,bool s){
        r->parent = dst;
        dst->son[s] = r;
    }
    node_t* find(node_t *r,int rank){
        while(true){
            push_down(r);
            //printf("v:%d,%d\n",r->val,r==null);
            if(r->son[0]->size > rank)
                r = r->son[0];
            else if(r->son[0]->size == rank)
                return r;
            else
                rank -= r->son[0]->size+1,r = r->son[1];
        }
    }
    node_t* build(T *a,int l,int r,int sl,int sr){
        if(l>r) return null;
        int mid = (l+r)>>1;
        //printf("l:%d r:%d mid:%d\n",l,r,mid);
        node_t *now = newnode(a[mid]);
        if(l!=r){
            node_t *ltree = build(a,l,mid-1,sl,sr),*rtree = build(a,mid+1,r,sl,sr);
            link(ltree,now,0),link(rtree,now,1);
        }
        if(l == sl && now->son[0] == null){
            node_t *lb = newnode();
            link(lb,now,0);
        }
        if(r == sr && now->son[1] == null){
            node_t *rb = newnode();
            link(rb,now,1);
        }
        maintain(now);
        if(l == sl&&r == sr)
            root = now;
        return now;
    }
    node_t* push_down(node_t *r){
        if(r == null) return null;
        if(r->rev){
            swap(r->son[0],r->son[1]);
            r->son[0]->rev^=1,r->son[1]->rev^=1;
            r->rev = 0;
        }
        return r;
    }
    void rotate(node_t *r){
        push_down(r->parent),push_down(r);
        node_t* rp = r->parent;
        bool re = get_p(r);
        link(r,rp->parent,get_p(rp));
        link(r->son[~re],rp,re);
        link(rp,r,~re);
        maintain(rp),maintain(r);
    }
    void splay(node_t *r,node_t *target){
        while(r->parent!=target){
            push_down(r->parent);
            if(r->parent->parent==target){
                rotate(r);
            }
            else{
                if(get_p(r) == get_p(r->parent))
                    rotate(r->parent),rotate(r);
                else
                    rotate(r),rotate(r);
            }
        }
    }
    node_t* select(node_t *r,int b,int e){
        node_t *lb = find(r,b-1);
        node_t *rb = find(r,e+1);
        splay(lb,null);
        splay(rb,lb);
        return rb->son[0];
    }
    void reverse(int b,int e){
        node_t *range = select(root,b,e);
        range->rev^=1;
    }
    void print(node_t *r,int depth = 0){
        if(r == null) return;
        else{
            print(r->son[0],depth+1);
            for(int i = 0;i<depth;i++)
                putchar(' ');
            printf("v:%d,size:%d,rev?:%d,son:%d %d,depth:%d\n",r->val,r->size,r->rev,r->son[0]!=null,r->son[1]!=null,depth);
            print(r->son[1],depth+1);
        }
    }
};

splay_t<int,2000> s;
int a[2000],n,m;


int main(){
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    printf("Finish reading.\n");
    s.build(a,1,n,1,n);
    printf("Finish building.\n");
    for(int i = 0;i<m;i++){
        int x,y;
        scanf("%d",&x);
        if(x>0){
            scanf("%d",&y);
            s.reverse(x,y);
        }
        else if(x == 0){
            s.print(s.root);
        }
        else{
            scanf("%d",&y);
            s.splay(s.find(s.root,y),s.null);
        }
        printf("Finish operatings.\n");
    }
    return 0;
}