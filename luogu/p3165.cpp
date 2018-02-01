#include <cstdio>
#include <algorithm>
using namespace std;

struct splat_t{
    struct node_t{
        int val,size;
        bool rev;
        node_t *p,*son[2],**root,**null;
        inline bool get_p(){return p->son[1] == this;}
        inline void init(node_t **root,node_t **null){this->null = null,this->root = root;}
        inline int lsize(){return son[0]->size;}
        inline int rsize(){return son[1]->size;}
        inline void update(){size = lsize()+rsize()+1;}
        inline void link(node_t *dst,int tmp){
            dst->son[tmp] = this;
            this->p = dst;
        }
        inline void push_down(){
            if(rev){
                swap(son[0],son[1]);
                son[0]->rev^=1,son[1]->rev^=1;
                rev = 0;
            }
        }
        inline void rotate(){
            p->push_down(),push_down();
            node_t *rp = p;int re = get_p();
            link(rp->p,re);
            son[1-re]->link(rp,re);
            rp->link(this,1-re);
            rp->update(),update();
        }
        inline node_t* splay(node_t *tar = NULL){
            if(tar == NULL) tar = *null;
            p->push_down(),push_down();
            while(p!=tar){
                if(p->p == tar)
                    rotate();
                else if(p->get_p() == get_p())
                    p->rotate(),rotate();
                else
                    rotate(),rotate();
            }
            return this;
        }
    };
};

int main(){
    return 0;

}