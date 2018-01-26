#include <cstdio>
#include <cstdlib>
#include <ctime>
#define newnode (&pool[treapcnt++])
#define MAX (0x3f3f3f3f)
using namespace std;

inline int qr(){
    int f = 1,s = 0;char ch = getchar();
    while(ch<'0'||ch>'9'){
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9'){
        s = (s<<3)+(s<<1)+ch-48;
        ch = getchar();
    }
    return f*s;
}

int n;

struct node{
    int key,cnt,size,p;
    node *child[2];
};

struct treap{
    int treapcnt;
    node pool[500000];
    node *root, *null;
    treap(){
        treapcnt = 0;
        null = newnode;
        null->cnt = null->size = 0;
        null->p = MAX;null->key = -MAX;
        null->child[0] = null->child[1] = null;
        root = null;
        srand(time(NULL));
    }
    void update(node *nown){
        nown->size = nown->cnt + nown->child[0]->size + nown->child[1]->size;
    }
    void rotate(node *&r,int tmp){//0左旋，1右旋
        node *t = r->child[1-tmp];
        r->child[1-tmp] = t->child[tmp];
        t->child[tmp] = r;
        update(r);update(t);
        r = t;
    }
    void __insert(node *&r,int k){
        if(r == null){
            r = newnode;
            r->cnt = r->size = 1;
            r->key = k;r->p = rand();
            r->child[0] = r->child[1] = null;
        }
        else{
            if(r->key == k)
                r->cnt++;
            else{
                int tmp = k > r->key;
                __insert(r->child[tmp],k);
                if(r->child[tmp]->p < r->p)
                    rotate(r,1-tmp);
            }
        }
        update(r);
    }
    void __erase(node *&r,int k){
        if(r->key == k){
            if(r->cnt > 1)
                r->cnt--;
            else{
                if(r->child[0] == null && r->child[1] == null)
                    r = null;
                else{
                    int tmp = r->child[0]->key < r->child[1]->key;
                    rotate(r,1-tmp);
                    __erase(r,k);
                }
            }
        }
        else{
            int tmp = r->key < k;
            __erase(r->child[tmp],k);
        }
        update(r);
    }
    void __print(node *r){
        if(r == null) return;
        else{
            __print(r->child[0]);
            printf("key:%d cnt:%d size:%d P:%d child:%d %d\n",r->key,r->cnt,r->size,r->p,r->child[0]!=null,r->child[1]!=null);
            __print(r->child[1]);
        }
    }
    node *findnode(node *r,int tmp){//0最小，1最大
        if(r->child[tmp] == null)
            return r;
        else
            return findnode(r->child[tmp],tmp);
    }
    node *loworup(int k,int t){//0代表前驱，1代表后继
        node *last = null;
        node *nown = root;
        while(nown->key!=k&& nown != null){
            int tmp = nown->key < k;
            if(1-tmp == t) last = nown;
            nown = nown->child[tmp];
        }
        if(nown->child[t]==null)
            return last;
        else
            return findnode(nown->child[t],1-t); 
    }
    int __getrank(node *r,int k){
        int res = 0;
        if(r->key == k||r == null)
            return r->child[0]->size +1;
        else if(k < r->key)
            return __getrank(r->child[0],k);
        else
            return __getrank(r->child[1],k) + r->child[0]->size +r->cnt;
    }
    node* __qrank(node *r,int rank){
        rank -= r->child[0]->size;
        if(rank<=0)
            return __qrank(r->child[0],rank + r->child[0]->size);
        else if(rank <= r->cnt)
            return r;
        else
            return __qrank(r->child[1],rank - r->cnt);
    }
    void insert(int k){
        __insert(root,k);
    }
    void erase(int k){
        __erase(root,k);
    }
    void print(){
        __print(root);
    }
    int lower(int k){
        return loworup(k,0)->key;
    }
    int upper(int k){
        return loworup(k,1)->key;
    }
    int getrank(int k){
        return __getrank(root,k);
    }
    int qrank(int k){
        return __qrank(root,k)->key;
    }
};

treap a;

int main(){
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    scanf("%d",&n);
    
    for(int i = 0;i<n;i++){
        int op,x;
        op = qr();x = qr();
        if(op == 1)
            a.insert(x);
        else if(op == 2)
            a.erase(x);
        else if(op == 3)
            printf("%d\n",a.getrank(x));
        else if(op == 4)
            printf("%d\n",a.qrank(x));
        else if(op == 5)
            printf("%d\n",a.lower(x));
        else if(op == 6)
            printf("%d\n",a.upper(x));
        else if(op == 7)
            a.print();
    }
    return 0;
}
