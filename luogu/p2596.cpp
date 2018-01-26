#include <cstdio>
#include <cstdlib>
#include <ctime>
#define newnode (&(pool[treapcnt++]))
using namespace std;

struct node{
    int id,val,p,size;
    node *son[2];
};

struct treap{
    int treapcnt;
    node pool[200000],*root,*null;
    node *id_to[200000];
    treap(){
        treapcnt = 0;
        null = newnode;
        null->id=null->size=null->val=0;
        null->p = 0x3f3f3f3f;
        null->son[0] = null->son[1] = null;
        root = null;
        srand(time(NULL));
    }
    void update(node *r){
        r->size = r->son[0]->size+r->son[1]->size+1;
    }
    void rotate(node *&r,int tmp){
        node *t = r->son[1-tmp];
        r->son[1-tmp] = t->son[tmp];
        t->son[tmp] = r;
        update(r);update(t);
        r = t;
    }
    void __insert(node *&r,int i,int v){
        if(r == null){
            r = newnode;
            r->id=i;r->val = v;r->p = rand();
            r->son[0] = r->son[1] = null;
            id_to[i] = r;
        }
        else{
            int tmp = v > r->val;
            __insert(r->son[tmp],i,v);
            if(r->son[tmp]->p < r->p)
                rotate(r,1-tmp);
        }
        update(r);
    }
    void __erase(node *&r,int v){
        if(r->val == v){
            if(r->son[0]==null && r->son[1]==null){
                id_to[r->id] = null;
                r = null;
            }
            else{
                int tmp = r->son[0]->p > r->son[1]->p;
                rotate(r,1-tmp);
                __erase(r->son[1-tmp],v);
            }
        }
        else{
            int tmp = v > r->val;
            __erase(r->son[tmp],v);
        }
        update(r);
    }
    void __print(node *r){
        if(r == null) return;
        else{
            __print(r->son[0]);
            printf("val:%d id:%d size:%d P:%d child:%d %d\n",r->val,r->id,r->size,r->p,r->son[0]!=null,r->son[1]!=null);
            __print(r->son[1]);
        }
    }
    void insert(int id,int v){
        __insert(root,id,v);
    }
    void erase(int v){
        __erase(root,v);
    }
    void print(){
        __print(root);
    }
};

treap x;

int n;

int main(){
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        int op;scanf("%d",&op);
        if(op == 1){
            int id,v;
            scanf("%d %d",&id,&v);
            x.insert(id,v);
        }
        if(op == 2){
            int v;
            scanf("%d",&v);
            x.erase(v);
        }
        if(op == 0){
            x.print();
        }
    }
    return 0;
}