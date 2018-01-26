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
    void __insert(node *&r,int valw,int valc){
        if(r == null){
            r = newnode;
            r->w = r->sumw = valw;r->c = r->sumc = valc;r->cnt = 1;
            r->son[0] = r->son[1] = null;
            r->p = rand();
        }
        else{
            if(valc == r->c)
                return;
            else{
                int tmp = valc > r->c;
                __insert(r->son[tmp],valw,valc);
                if(r->son[tmp]->p < r->p)
                    rotate(r,1-tmp);
            }
            update(r);
        }
    }
    void __erase(node *r,int op){//op == 0代表最小值，op == 1代表最大值
        return;
    }
};



int main(){
    return 0;
}