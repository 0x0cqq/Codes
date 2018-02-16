#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAXN = 100000;

struct node_t{
    int val,p;
    int lmax,rmax,maxn,sum;
    int tag;
    bool rev;
    node_t *son[2];
};


struct fhqtreap{
    node_t pool[MAXN];
    node_t *root,*null;
    int cnt;
    void newnode(node_t *&r,int val = 0){
        r = &pool[cnt++];
        r->val = val;
        r->lmax = r->rmax = r->maxn = r->sum = val;
        r->son[0] = r->son[1] = null;
        r->p = rand();
    }
    fhqtreap(){
        cnt = 0;srand(NULL);
        newnode(null);
        null->p = 2147483647;
        root = null;
    }
    void pushdown(node_t *n){
        n->son[0]->lmax =；
    }
};