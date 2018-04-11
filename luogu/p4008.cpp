#include <cstdio>
using namespace std;

template<int MAXN>
struct Splay{
    struct node_t{
        int val,siz;
        node_t **null,**root;
        node_t *son[2],*p;
        void init(node_t **root,node_t **null){
            this->null = null,this->root = root;
        }
        bool get_p(){
            return p->son[1] == this;
        }
        void maintain(){
            siz = son[0]->siz + son[1]->siz+1;
        }
        void link(node_t *dst,int s){
            p = dst;dst->son[s] = this;
        }
        void rotate(){
            node_t *rp = p;bool re = get_p();
            link(rp->p,rp->get_p());
            son[1-re]->link(rp,re);
            rp->link(this,1-re);
            rp->maintain(),maintain();
            if(p == *null) *root = this;
        }
        void splay(node_t *target = NULL){
            if(target == NULL) target = *null;
            while(p!=target){
                if(p->p == target)
                    rotate();
                else{
                    if(get_p() == p->get_p())
                        p->rotate(),rotate();
                    else
                        rotate(),rotate();
                }
            }
        }
    };
    node_t *null,*root;
    node_t pool[MAXN<<2];int cnt;
    void newnode(node_t *&r){
        r = &pool[cnt++];
        r->son[0] = r->son[1] = r->p = null;
    }
    Splay(){
        cnt = 0;newnode(null);
        root = null;
        null->init(&root,&null);
    }
    node_t* find(int pos){//从小往大数第n个
        node_t *r = root;
        while(true){
            if(r->son[0]->siz > pos)
                r = r->son[0];
            else if(r->son[0]->siz == pos)
                return r;
            else
                pos-=r->son[0]->siz+1,r = r->son[1];
        }
    }
    node_t *build(int l,int r,char *a){
        if(l>r) return null;
        //printf("build:%d %d\n",l,r);
        node_t *now;newnode(now);now->init(&root,&null);
        int mid = (l+r)>>1;
        node_t *ls = build(l,mid-1,a),*rs = build(mid+1,r,a);
        ls->link(now,0),rs->link(now,1);
        now->val = a[mid];
        now->maintain();
        //print(now,0);
        return now;
    }
    inline void insert(int pos,int len,char *a){
        //在第pos个字符后面加入n个来自in的字符
        node_t *lb = find(pos),*rb = find(pos+1);
        //printf(":%d %d\n",lb->val,rb->val);
        lb->splay(),rb->splay(lb);
        build(0,len-1,a)->link(rb,0);
        rb->maintain(),lb->maintain();
    }
    inline void del(int pos,int len){
        //删除第pos个字符后面len个字符
        node_t *lb = find(pos),*rb = find(pos+len+1);
        lb->splay(),rb->splay(lb);
        rb->son[0] = null;
        rb->maintain(),lb->maintain();
    }
    inline void dfs(node_t *r,char *a){
        if(r->son[0] != null)
            dfs(r->son[0],a);
        a[r->son[0]->siz] = r->val;
        if(r->son[1] != null)
            dfs(r->son[1],a+ r->son[0]->siz+1);
    }
    inline void output(int pos,int len,char *a){
        node_t *lb = find(pos),*rb = find(pos+len+1);
        lb->splay(),rb->splay(lb);
        dfs(rb->son[0],a);
    }
    inline void print(node_t *r,int dep = 0){
        if(r == null) return;
        if(dep == 0)
            printf("-------------------\n");
        print(r->son[0],dep+1);
        for(int i = 0;i<dep;i++)
            putchar(' ');
        printf("val:%d(%c),ls:%d rs:%d dep:%d\n",r->val,r->val,r->son[0]!=null,r->son[1]!=null,dep);
        print(r->son[1],dep+1);
        if(dep == 0)
            printf("---------------------\n");
    }
};

char in[3000000],out[3000000];

Splay<3000000> s;

inline void insert(int pos,int len){
    getchar();
    for(int i = 0;i<len;i++){
        in[i] = getchar();
        //printf("in:%d\n",in[i]);
        if(in[i] == '\r'||in[i] == '\n')
            --i;
    }
    s.insert(pos,len,in);
}

inline void del(int pos,int len){
    s.del(pos,len);
}

inline void get(int pos,int len){
    s.output(pos,len,out);
    for(int i = 0;i<len;i++){
        putchar(out[i]);
    }
    putchar('\n');
}

void solve(){
    char op[20];int t,gb = 0;//gb为光标在哪个点之后
    op[0] = op[1] = ' ';s.root = s.build(0,1,op);
    scanf("%d",&t);
    for(int i = 1;i<=t;i++){
        scanf("%s",op);
        if(op[0] == 'M')
            scanf("%d",&gb);
        else if(op[0] == 'P')
            gb--;
        else if(op[0] == 'N')
            gb++;
        else if(op[0] == 'T')
            s.print(s.root,0),--i;
        else{
            int tmp;
            scanf("%d",&tmp);
            if(op[0] == 'I')
                insert(gb,tmp);
            else if(op[0] == 'D')
                del(gb,tmp);
            else if(op[0] == 'G')
                get(gb,tmp);
        }
    }
}

int main(){
    solve();
    return 0;
}