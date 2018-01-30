#include <cstdio>
#define MAX 2147483647
using namespace std;

struct splay_t{
    struct node_t{
        int val,size,lazy,cnt;
        node_t *son[2],*p;node_t **null,**root;
        bool get_p(){return p->son[1] == this;}
        void push_down(){
            if(this == *null) return;
            if(lazy) son[0]->lazy+=lazy,son[1]->lazy+=lazy,val+=lazy;
            lazy = 0;
        }
        void link(node_t *dst,bool re){p = dst;dst->son[re] = this;}
        void update(){size = son[0]->size + son[1]->size + cnt;}
        void init(node_t **null,node_t **root){this->null = null,this->root = root;}
        void rotate(){
            p->push_down();
            push_down();
            bool re = get_p();node_t *rp = p;
            link(rp->p,rp->get_p());
            son[1-re]->link(rp,re);
            rp->link(this,1-re);
            rp->update();update();
            if(p == *null) *root = this; 
        }
        void splay(node_t *tar = NULL){
            if(tar == NULL) tar = *null;
            while(p!=tar){
                p->push_down(),push_down();
                if(p->p == tar) rotate();
                else{
                    if(p->get_p()==get_p())
                        p->rotate(),rotate();
                    else rotate(),rotate();
                }
            }
        }
    };
    int treecnt;
    node_t pool[200000];
    node_t *null,*root;
    splay_t(){
        treecnt = 0;
        newnode(null);
        root = null;
        null->init(&null,&root);
        insert(MAX),insert(-MAX);
    }
    void newnode(node_t *&r,int val = 0){
        r = &pool[treecnt++];
        r->val = val;
        r->son[0] = r->son[1] = r->p = null;
    }
    inline void insert(int val){
        node_t **tar = &root,*parent = null;
        while(*tar!=null){
            (*tar)->size++;
            if((*tar)->val == val){
                (*tar)->cnt++;return;
            }
            else{
                parent = *tar;
                tar = &(*tar)->son[(*tar)->val<val];
            }
        }
        newnode(*tar,val);
        (*tar)->link(parent,parent->val<val);
        (*tar)->splay();
    }
};

int main(){
    return 0;
}