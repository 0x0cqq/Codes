#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;


struct treap{
    struct node_t{
        int val,p;
        node_t *son[2];
    };
    int treapcnt;
    node_t pool[50000];
    node_t *null, *root;
    treap(){
        treapcnt = 0;
        srand(time(NULL));
        newnode(null);
        null->p = 2147483647,null->val = 0x3f3f3f3f;
        root = null;
    }
    void newnode(node_t *&r,int val = 0){
        r = &(pool[treapcnt++]);
        r->p = rand(),r->son[0] = r->son[1] = null;
        r->val = val;
    }
    void rotate(node_t *&r,int tmp){//0左旋 1右旋
        node_t *t = r->son[1-tmp];
        r->son[1-tmp] = t->son[tmp];
        t->son[tmp] = r;
        r = t;
    }
    node_t *find(node_t *r,int val){
        if(r == null)
            return null;
        else{
            if(val == r->val) return r;
            int tmp = r->val < val;
            return find(r->son[tmp],val);
        }
    }
    node_t* __insert(node_t *&r,int v){
        if(r == null){
            newnode(r,v);
            return r;
        }
        else{
            if(r->val == v) return r;
            else{
                int tmp = r->val < v;
                node_t *ret = __insert(r->son[tmp],v);
                if(r->son[tmp]->p<r->p)
                    rotate(r,1-tmp);
                return ret;
            }
        }
    }
    node_t *loworup(int v,int f){
        node_t *t = root,*last = null;
        while(t!=null&&t->val!=v){
            int tmp = t->val<v;
            if(tmp != f) last = t;
            t = t->son[tmp];
        }
        if(t->son[1-f]!=null){
            t = t->son[1-f];
            while(t->son[f]!=null)
                t = t->son[f];
        }
        else{
            t = last;
        }
        return t;
    }
    int min_gap(int val){
        if(find(root,val)!=null)
            return 0;
        else{
            return min(abs(loworup(val,0)->val-val),abs(loworup(val,1)->val-val));
        }
    }
    void insert(int v){__insert(root,v);}
    void print(node_t *r = NULL,int depth = 0){//调试用
        if(r == NULL) r = root;
        if(r == null) return;
        else{
            print(r->son[0],depth+1);
            for(int i = 0;i<depth;i++) putchar(' ');//打印深度
            printf("val:%d P:%d son?:%d %d\n",r->val,r->p,r->son[0]!=null,r->son[1]!=null);
            print(r->son[1],depth+1);
        }
    }
};

treap x;

int n,t,res = 0;

int main(){
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        scanf("%d",&t);
        if(i!=0)
            res += x.min_gap(t);
        else
            res+=t;
        x.insert(t);
    }
    printf("%d\n",res);
}