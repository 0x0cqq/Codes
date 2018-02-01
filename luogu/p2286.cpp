#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;

struct treap{
    struct node_t{
        int val,p;
        node_t *son[2];
    };
    int treapcnt;node_t pool[100000];
    node_t *root,*null;
    treap(){
        treapcnt = 0;
        srand(time(NULL));
        newnode(null,0x3f3f3f3f);
        root = null,null->p = 2147483647;
    }
    node_t *find(int val){
        node_t *r = root;
        while(r->val!=val&&r!=null){
            r = r->son[r->val<val];
        }
        return r;
    }
    void rotate(node_t *&r,int tmp){
        node_t *t = r->son[1-tmp];
        r->son[1-tmp] = t->son[tmp],t->son[tmp] = r;
        r = t;
    }
    void newnode(node_t *&r,int val = 0){
        r = &(pool[treapcnt++]);
        r->val = val,r->p = rand();
        r->son[0] = r->son[1] = null;
    }
    void insert(node_t *&r,int val){
        if(r == null)
            newnode(r,val);
        else{
            int tmp = r->val<val;
            insert(r->son[tmp],val);
            if(r->son[tmp]->p<r->p)
                rotate(r,1-tmp);
        }
    }
    void erase(node_t *&r,int val){
        if(r ->val == val){
            if(r->son[0]==null&&r->son[1]==null)
                r = null;
            else{
                int tmp = r->son[0]->p > r->son[1]->p;
                rotate(r,1-tmp);
                erase(r,val);
            }
        }
        else{
            erase(r->son[r->val<val],val);
        }
    }
    node_t *loworup(int val,int t){
        node_t *r = root,*last = null;
        while(r->val!=val&&r!=null){
            int tmp = r->val<val;
            if(tmp!=t) last = r;
            r = r->son[tmp];
        }
        if(r->son[1-t]!=null){
            r = r->son[1-t];
            while(r->son[t]!=null)
                r = r->son[t];
        }
        else
            r = last;
        return r;
    }
    void print(node_t *r,int depth = 0){
        if(r == null) return;
        print(r->son[0],depth+1);
        for(int i = 0;i<depth;i++) putchar(' ');
        printf("val:%d,P:%d\n",r->val,r->p);
        print(r->son[1],depth+1);
    }
};

treap x;

int treestate = -1,res = 0,n;//1代表全是宠物，0代表全是领养者

void oper(int val,int tmp){//0代表宠物，1代表领养者
    if(x.root == x.null)
        x.insert(x.root,val),treestate = 1-tmp;
    else if(tmp == treestate){
        if(x.find(val) != x.null)
            x.erase(x.root,val);
        else{
            treap::node_t *a = x.loworup(val,0),*b = x.loworup(val,1),ret;
            if(abs(b->val-val)<abs(a->val-val))
                res += abs(b->val-val),x.erase(x.root,b->val);
            else
                res += abs(a->val-val),x.erase(x.root,a->val);
        }
    }
    else if(tmp != treestate)
        x.insert(x.root,val);
}


int main(){
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        int op,w;
        scanf("%d %d",&op,&w);
        oper(w,op);
        res%=1000000;
    }
    printf("%d\n",res);
    return 0;
}