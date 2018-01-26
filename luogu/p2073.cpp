#include <cstdio>
#include <cstdlib>
#include <ctime>
#define newnode (&pool[treapcnt++])
using namespace std;


inline int qr(){
    int f = 1,s = 0;char ch = getchar();
    while(ch<'0'||ch>'9'){
        if(ch == '-') f = -1;
        ch = getchar(); 
    }
    while(ch>='0'&&ch<='9'){
        s = (s<<3)+(s<<1)+ch - 48;
        ch = getchar();
    }
    return f*s;
}

struct node{
    int w,c,sumw,sumc,p;
    node *son[2];
};

struct treap{
    int treapcnt;
    node pool[200000],*null,*root;
    treap(){
        treapcnt = 0;
        null = newnode;
        null->w=null->c=null->sumw=null->sumc=null->p = 0;
        null->son[0] = null->son[1] = null;
        root = null;srand(time(NULL));
    }
    void update(node *r){
        r->sumw = r->son[0]->sumw + r->son[1]->sumw + r->w ;
        r->sumc = r->son[0]->sumc + r->son[1]->sumc + r->c ;
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
            r->w = valw;r->c = valc;
            r->son[0] = r->son[1] = null;
            update(r);
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
    void __erase(node *&r,int op){//op == 0代表最小值，op == 1代表最大值
        if(r->son[op] == null){
            r = r->son[1-op];
            update(r);
        }
        else{
            __erase(r->son[op],op);
            update(r);
        }
        return;
    }
    void __print(node *r){
        if(r == null) return;
        printf("w:%d c:%d p:%d sumw:%d sumc:%d son:%d %d\n",r->w,r->c,r->p,r->sumw,r->sumc,r->son[0] != null,r->son[1] != null);
        __print(r->son[0]);__print(r->son[1]);
    }
    void insert(int valw,int valc){
        __insert(root,valw,valc);
    }
    void delete_min(){
        __erase(root,0);
    }
    void delete_max(){
        __erase(root,1);
    }
    void print(){
        __print(root);
    }
};

treap w;


int main(){
    int a,b,c;
    while(true){
        a = qr();
        if(a == -1)
            break;
        else if(a == 1){
            b = qr();c =qr();
            w.insert(b,c);
        }
        else if(a == 2)
            w.delete_max();
        else if(a == 3)
            w.delete_min();
        else if(a == 0)
            w.print();
    }
    printf("%d %d\n",w.root->sumw,w.root->sumc);
    return 0;
}