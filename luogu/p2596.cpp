#include <cstdio>
#include <cstdlib>
#include <ctime>
#define maxint 2147483647
#define newnode (&(pool[treapcnt++]))
using namespace std;

struct node{
    int id,val,p,size;
    node *son[2];
};

struct treap{
    int treapcnt,b,e;
    node pool[200000],*root,*null;
    node *id_to[200000];
    treap(){
        treapcnt = 0;b = e = 0;
        null = newnode;
        null->id=null->size=null->val=0;
        null->p = maxint;
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
                return;
            }
            else{
                int tmp = r->son[0]->p > r->son[1]->p;
                rotate(r,1-tmp);
                __erase(r,v);
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
    int __ask_rank(node *r,int v){
        if(r->val == v) return r->son[0]->size;
        int tmp = v > r->val;
        if(tmp == 0) return __ask_rank(r->son[0],v);
        else return r->son[0]->size+__ask_rank(r->son[1],v)+1;
    }
    node *__find_rank(node *r,int rank){
        if(rank <= r->son[0]->size)
            return __find_rank(r->son[0],rank);
        rank -= (r->son[0]->size+1);
        if(rank == 0) return r;
        else return __find_rank(r->son[1],rank);
    }
    node *find_minormax(node *r,int tmp){
        while(r->son[tmp]!=null)
            r = r->son[tmp];
        return r;
    }
    node *loworup(int v,int t){//0代表前驱，1代表后继
        node *last = null,*nown = root;
        while(nown->val!=v){
            int tmp = v > nown->val;
            if(tmp!=t) last = nown;
            nown = nown->son[tmp];
        }
        if(nown->son[t]!=null)
            last = find_minormax(nown->son[t],1-t);
        return last;
    }
    void insert_to_bottom(int id){
        __insert(root,id,++e);
    }
    void insert_to_top(int id){
        __insert(root,id,--b);
    }
    int ask_rank(int id){
        return __ask_rank(root,id_to[id]->val);
    }
    int query_rank(int rank){
        return __find_rank(root,rank)->id;
    }
    void change_pos(int id,int t){
        if(t == 0) return;
        else if(t == -1) t = 0;
        node *nown = id_to[id];
        node *dst = loworup(nown->val,t);
        nown->id = dst->id;dst->id = id;
        id_to[nown->id] = nown;id_to[dst->id] = dst; 
    }
    void insert(int id,int v){
        __insert(root,id,v);
    }
    void erase(int id){
        __erase(root,id_to[id]->val);
    }
    void print(){
        __print(root);
    }
};

treap x;

int n,m;

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++){
        int t;
        scanf("%d",&t);
        x.insert_to_bottom(t);
    }
    for(int i = 0;i<m;i++){
        char ch[10];int t,d;
        scanf("%s",ch);
        if(ch[0] == 'T'){
            scanf("%d",&t);
            x.erase(t);
            x.insert_to_top(t);
        }
        else if(ch[0] == 'B'){
            scanf("%d",&t);
            x.erase(t);
            x.insert_to_bottom(t);
        }
        else if(ch[0] == 'A'){
            scanf("%d",&t);
            printf("%d\n",x.ask_rank(t));
        }
        else if(ch[0] == 'Q'){
            scanf("%d",&t);
            printf("%d\n",x.query_rank(t));
        }
        else if(ch[0] == 'I'){
            int k;
            scanf("%d %d",&t,&k);
            x.change_pos(t,k);
        }
        else if(ch[0] == 'P'){
            x.print();
        }
    }
    return 0;
}