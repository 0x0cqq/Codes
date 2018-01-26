#include <cstdio>
#include <cstdlib>
#include <ctime>
#define newnode (&pool[treapcnt++])
using namespace std;

struct node{
    int w,c,sumw,sumc,p,cnt;
    node *son[2];
};

struct treap{
    int treapcnt;
    node pool[200000],*null,*root;
    treap(){
        treapcnt = 0;
        null = newnode;
        null->w=null->c=null->sumw=null->sumc=null->p=null->cnt = 0;
        null->son[0] = null->son[1] = null;
        root = null;srand(time(NULL));
    }
    void update(node *r){
        r->sumw = r->son[0]->sumw + r->son[1]->sumw + r->w * r->cnt;
        r->sumc = r->son[0]->sumc + r->son[1]->sumc + r->c * r->cnt;
    }
    void rotate(node *&r,int tmp){//0左旋，1右旋
        node *t = r->son[1-tmp];
        r->son[1-tmp] = t->son[tmp];
        t->son[tmp] = r;
        update(r);update(t);
        r = t;
    }
    void insert(node *&r,int valw,int valc){
        if(r == null){
            r = newnode;
            r->w = r->sumw = valw;r->c = r->sumc = valc;r->cnt = 1;
            r->son[0] = r->son[1] = null;
        }
        else{
            if(valc == r->c)
                return;
            else{
                int tmp = valc > r->c;
                insert(r->son[tmp],valw,valc);
                if(s)
            }
        }
    }
};



int main(){
    return 0;
}