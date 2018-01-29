#include <cstdio>
#include <cstdlib>
#include <ctime>
#define maxint  2147483647
#define newnode (&(pool[treapcnt++]))
using namespace std;

struct treap{
    struct node{
        int val,p,size,cnt;
        node *son[2];
    };
    int treapcnt;
    node pool[200000],*root,*null;
    treap(){
        treapcnt = 0;
        null = newnode;
        null->size=null->val=0;
        null->p = maxint;
        null->son[0] = null->son[1] = null;
        root = null;
        srand(time(NULL));
    }
    void update(node *r){
        r->size = r->son[0]->size+r->son[1]->size+r->cnt;
    }
    void rotate(node *&r,int tmp){//0左旋，1右旋
        node *t = r->son[1-tmp];
        r->son[1-tmp] = t->son[tmp];
        t->son[tmp] = r;
        update(r);update(t);
        r = t;
    }
    void __insert(node *&r,int v){
        if(r == null){
            r = newnode;
            r->val = v;r->cnt = 1;r->p = rand();
            r->son[0] = r->son[1] = null;
        }
        else{
            if(r->val == v) 
                r->cnt++;
            else{
                int tmp = v > r->val;
                __insert(r->son[tmp],v);
                if(r->son[tmp]->p < r->p)
                    rotate(r,1-tmp);
            }
        }
        update(r);
    }
    void __erase(node *&r,int v){
        if(r->val == v){
            if(r->cnt > 1) r->cnt--;
            else{
                if(r->son[0]==null && r->son[1]==null){
                    r = null;return;
                }
                else{
                    int tmp = r->son[0]->p > r->son[1]->p;
                    rotate(r,1-tmp);
                    __erase(r,v);
                }
            }
        }
        else{
            int tmp = v > r->val;
            __erase(r->son[tmp],v);
        }
        update(r);
    }
    void __print(node *r,int depth = 0){
        if(r == null) return;
        else{
            __print(r->son[0],depth+1);
            for(int i = 0;i<depth;i++) putchar(' ');
            printf("val:%d cnt:%d size:%d P:%d son:%d %d\n",r->val,r->cnt,r->size,r->p,r->son[0]!=null,r->son[1]!=null);
            __print(r->son[1],depth+1);
        }
    }
    int __getrank(node *r,int v){
        if(r->val == v||r == null)
            return r->son[0]->size +1;
        else if(v < r->val)
            return __getrank(r->son[0],v);
        else
            return __getrank(r->son[1],v) + r->son[0]->size +r->cnt;
    }
    node* __qrank(node *r,int rank){
        rank -= r->son[0]->size;
        if(rank<=0)
            return __qrank(r->son[0],rank + r->son[0]->size);
        else if(rank <= r->cnt)
            return r;
        else
            return __qrank(r->son[1],rank - r->cnt);
    }
    node *find_minormax(node *r,int tmp){
        while(r->son[tmp]!=null)
            r = r->son[tmp];
        return r;
    }
    node *loworup(int v,int t){//0代表前驱，1代表后继
        node *last = null,*nown = root;
        while(nown->val!=v && nown!=null){
            int tmp = v > nown->val;
            if(tmp!=t) last = nown;
            nown = nown->son[tmp];
        }
        if(nown->son[t]!=null)
            last = find_minormax(nown->son[t],1-t);
        return last;
    }
    void insert(int v){__insert(root,v);}
    void erase(int v){__erase(root,v);}
    int getrank(int v){return __getrank(root,v);}
    int qrank(int rank){return __qrank(root,rank)->val;}
    int lower(int v){return loworup(v,0)->val;}
    int upper(int v){return loworup(v,1)->val;}
    void print(){__print(root);}
};

treap w;

int n;

int main(){
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        int op, x;
        scanf("%d %d",&op,&x);
        if(op == 1)      w.insert(x);
        else if(op == 2) w.erase(x);
        else if(op == 3) printf("%d\n",w.getrank(x));
        else if(op == 4) printf("%d\n",w.qrank(x));
        else if(op == 5) printf("%d\n",w.lower(x));
        else if(op == 6) printf("%d\n",w.upper(x));
        else if(op == 0) w.print();
    }
    return 0;
}