#include <cstdio>
using namespace std;

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
        void link(node_t *dst,int s){
            dst->son[s] = this;
            this->p = dst;
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
        void splay(node_t *tar = NULL){
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
        node_t *lb,*rb;
        newnode(lb),newnode(rb);
        root = lb;
        lb->v[0] = lb->v[1] = -1,rb->v[0] = rb->v[1] = 0x3f3f3f3f;
        rb->link(lb,1);
        rb->maintain(),lb->maintain();
    }
    node_t* find(int rank){//rank就是有多少个数比这个小
        node_t *r = root;
        while(true){
            if(rank < r->son[0]->siz)
                r = r->son[0];
            else if(rank == r->son[0]->siz)
                return r;
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
        //printf("%d %d L:%d %d R:%d %d\n",get_rank(l,1)-1,get_rank(r+1,0),lb->v[0],lb->v[1],rb->v[0],rb->v[1]);
        node_t *newn;newnode(newn);
        newn->v[0] = l,newn->v[1] = r;
        lb->splay();rb->splay(lb);
        int ans = rb->son[0]->siz;
        newn->link(rb,0);
        newn->maintain(),rb->maintain();lb->maintain();
        return ans;
    }
    int get_size(){
        return root->siz - 2;
    }
    void print(node_t *r,int dep = 0){
        if(r == null) return;
        if(dep == 0)
            printf("-------------------\n");
        print(r->son[0],dep+1);
        for(int i = 0;i<dep;i++)
            putchar(' ');
        printf("val:%d %d, siz:%d, ls:%d rs:%d, dep:%d\n",r->v[0],r->v[1],r->siz,r->son[0]!=null,r->son[1]!=null,dep);
        print(r->son[1],dep+1);
        if(dep == 0)
            printf("---------------------\n");
    }
};

Splay<2000000> t;

int n;

void solve(){
    scanf("%d",&n);
    char op[20];int l,r;
    for(int i = 1;i<=n;i++){
        scanf("%s",op);
        if(op[0] == 'A'){
            scanf("%d %d",&l,&r);
            printf("%d\n",t.insert(l,r));
        }
        else if(op[0] == 'B'){
            printf("%d\n",t.get_size());
        }
        else if(op[0] == 'P'){
            --i;
            t.print(t.root);
        }
    }
}

int main(){
    solve();
    return 0;
}