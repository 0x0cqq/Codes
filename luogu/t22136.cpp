// luogu-judger-enable-o2
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unistd.h>
using namespace std;

struct wupin{
    int id,height;
}w[100100];

struct splay_t{
    struct node_t{
        int val,size;
        bool rev;
        node_t *p,*son[2],**root,**null;
        inline bool get_p(){return p->son[1] == this;}
        inline void init(node_t **root,node_t **null){this->null = null,this->root = root;}
        inline int lsize(){return son[0]->size;}
        inline int rsize(){return son[1]->size;}
        inline void update(){size = lsize()+rsize()+1;}
        inline void link(node_t *dst,int tmp){
            dst->son[tmp] = this;
            this->p = dst;
        }
        inline void push_down(){
            if(this == *null) return;
            if(rev){
                swap(son[0],son[1]);
                son[0]->rev^=1,son[1]->rev^=1;
                rev = 0;
            }
        }
        inline void rotate(){
            p->push_down(),push_down();
            node_t *rp = p;bool re = get_p();
            link(rp->p,rp->get_p());
            son[1-re]->link(rp,re);
            rp->link(this,1-re);
            rp->update(),update();
            if(p == *null) *root = this;
        }
        inline node_t* splay(node_t *tar = NULL){
            if(tar == NULL) tar = *null;
            if(this == *null){
                printf("wrong\n");
                return *null;
            }
            p->push_down(),push_down();
            while(p!=tar){
                if(p->p == tar)
                    rotate();
                else if(p->get_p() == get_p())
                    p->rotate(),rotate();
                else
                    rotate(),rotate();
            }
            return this;
        }
        node_t *upper(){
            splay();
            if(son[1] == *null) printf("impossible!\n");
            else{
                push_down();
                node_t *r = son[1];
                while(true){
                    r->push_down();
                    if(r->son[0] == *null)
                        break;
                    r = r->son[0];
                }
                return r;
            }
            return *null;
        }
        node_t *lower(){
            splay();
            if(son[0] == *null) printf("impossible!\n");
            else{
                push_down();
                node_t *r = son[0];
                while(true){
                    r->push_down();
                    if(r->son[1] == *null)
                        break;
                    r = r->son[1];
                }
                return r;
            }
            return *null;
        }
    };
    int cnt;
    node_t pool[110000],*to[110000],*null,*root;
    splay_t(){
        cnt = 0;
        null = newnode();
        null->size = 0;
    }
    node_t *newnode(int val = 0){
        node_t *r = &pool[cnt++];
        r->init(&root,&null);
        r->val = val;
        r->p = null,r->son[0] = r->son[1] = null;
        r->size = 1,r->rev = 0;
        return r;
    }
    node_t* build(wupin *a,int l,int r){
        if(l>r) return null;
        int mid = (l+r)>>1;
        node_t *ret = newnode(a[mid].height);
        to[a[mid].height] = ret;
        build(a,l,mid-1)->link(ret,0);
        build(a,mid+1,r)->link(ret,1);
        ret->update();
        return ret;
    }
    void print(node_t *r = NULL,int depth = 0){
        if(r == NULL) r = root;
        //printf("%d %d\n",r->val,depth);
        if(r == null) return;
        else{
            print(r->son[0],depth+1);
            for(int i = 0;i<depth;i++)
                putchar(' ');
            printf("v:%d,size:%d,rev?:%d,son:%d %d,depth:%d\n",r->val,r->size,r->rev,r->son[0]!=null,r->son[1]!=null,depth);
            print(r->son[1],depth+1);
        }
    }
};

splay_t s;


int n;

bool cmp1(wupin,wupin);bool cmp2(wupin,wupin);

vector<pair<int,int> > ans;

void find(){
    for(int i = n;i>=1;i--){
        //printf("----------------------------------\n");
        //printf("%d\n",i);
        //s.print();
        splay_t::node_t *lbound = s.to[i]->lower();
        splay_t::node_t *rbound = s.to[i+1];
        lbound->splay();
        rbound->splay(lbound);
        if(lbound->lsize()+1!=i)
            ans.push_back(make_pair(lbound->lsize()+1,i));
        rbound->son[0]->rev^=1;
        //sleep(10);
    }
    int tmp = ans.size();
    printf("%d\n",tmp);
    for(int i = 0;i<tmp;i++){
        printf("%d %d\n",ans[i].first,ans[i].second);
    }
}

int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%d",&w[i].height);
        w[i].id = i;
    }
    sort(w+1,w+n+1,cmp2);
    for(int i = 1;i<=n;i++)
        w[i].height = i;
    sort(w+1,w+n+1,cmp1);
    w[0].height = 0;
    w[n+1].height = n+1;
    s.root = s.build(w,0,n+1);
    find();
    return 0;
}




bool cmp1(wupin a,wupin b){
    return a.id<b.id;
}

bool cmp2(wupin a,wupin b){
    if(a.height!=b.height)
        return a.height<b.height;
    else
        return a.id<b.id;
}