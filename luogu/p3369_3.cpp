#include <cstdio>
#include <cstdlib>
#include <ctime>
#define maxint  2147483647
using namespace std;

template<size_t siz>//模版T,需要有等于不等于和小于运算符
struct treap{
    private:
    struct node_t{
        int val;
        int p,size,cnt;
        node_t *son[2];
    };
    int treapcnt;
    node_t pool[siz<<1],*root,*null;
    void newnode(node_t *&r){
        r = &pool[treapcnt++];
        r->son[0] = r->son[1] = null;
    }
    void update(node_t *r){
        r->size = r->son[0]->size+r->son[1]->size+r->cnt;
    }
    void rotate(node_t *&r,int tmp){//0左旋，1右旋
        node_t *t = r->son[1-tmp];//找到需要旋上来的节点
        r->son[1-tmp] = t->son[tmp];//将被选节点的被遮蔽的儿子交给上面的节点
        t->son[tmp] = r;//将r作为t的儿子
        update(r),update(t);//注意更新顺序！先儿子后父亲
        r = t;//通过引用更改上方节点的儿子
    }
    void __insert(node_t *&r,int v){//r代表当前节点，v代表关键字
        if(r == null){//如果r的地方已经没有节点
            newnode(r);//新建节点，并通过引用添加至上面节点的儿子
            r->val = v,r->cnt = 1,r->p = rand();//对相关信息的设置
        }
        else{
            if(r->val == v) //如果已经添加过，直接给数量++
                r->cnt++;
            else{
                int tmp = r->val < v;
                __insert(r->son[tmp],v);//递归更改
                if(r->son[tmp]->p < r->p)//维护treap性质
                    rotate(r,1-tmp);
            }
        }
        update(r);//不要忘了更新！
    }
    void __erase(node_t *&r,int v){
        if(r->val == v){//已经找到
            if(r->cnt > 1) r->cnt--;
            else{
                if(r->son[0]==null && r->son[1]==null){//已经没有子节点，直接删除
                    r = null;return;
                }
                else{//还有子节点，
                    int tmp = r->son[1]->p < r->son[0]->p;
                    rotate(r,1-tmp); //找到其中随机权值较小的一个旋转替换当前节点
                    __erase(r,v);//递归删除 注意此处r已经发生了变化
                }
            }
        }
        else{//还没找到
            int tmp = r->val < v;
            __erase(r->son[tmp],v);//递归寻找
        }
        update(r);//不要忘了更新！
    }
    void __print(node_t *r,int depth = 0){//调试用
        if(r == null) return;
        else{
            __print(r->son[0],depth+1);
            for(int i = 0;i<depth;i++) putchar(' ');//打印深度
            printf("val:%d cnt:%d size:%d P:%d son?:%d %d\n",r->val,r->cnt,r->size,r->p,r->son[0]!=null,r->son[1]!=null);
            __print(r->son[1],depth+1);
        }
    }
    int __getrank(node_t *r,int v){//查找数v的排名
        if(r->val == v||r == null)//记得判空！
            return r->son[0]->size +1;
        else if(v < r->val)
            return __getrank(r->son[0],v);
        else
            return __getrank(r->son[1],v) + r->son[0]->size + r->cnt;
    }
    node_t* __qrank(node_t *r,int rank){//查找以rank排名的数
        rank -= r->son[0]->size;
        if(rank<=0)
            return __qrank(r->son[0],rank + r->son[0]->size);
        else if(rank <= r->cnt)
            return r;
        else
            return __qrank(r->son[1],rank - r->cnt);
    }
    node_t *find_minormax(node_t *r,int tmp){
        //寻找以r为根节点的树上最大或最小节点
        while(r->son[tmp]!=null)
            r = r->son[tmp];
        return r;
    }
    node_t *loworup(int v,int t){//0代表前驱，1代表后继
        node_t *last = null,*nown = root;//last表示上一个没有当前寻找方向的节点
        while(nown->val!=v && nown!=null){//记得判空!
            int tmp =  nown->val < v;
            if(tmp!=t) last = nown;
            nown = nown->son[tmp];
        }
        if(nown->son[t]!=null)//有子节点
            last = find_minormax(nown->son[t],1-t);//寻找对应方向子节点的最小or最大值
        return last;
    }
    public:
    treap(){
        treapcnt = 0;
        newnode(null);
        null->size = null->val=0;
        null->p = maxint;
        root = null;
        srand(time(NULL));
    }
    void insert(int v){__insert(root,v);}
    void erase(int v){__erase(root,v);}
    int getrank(int v){return __getrank(root,v);}
    int qrank(int rank){return __qrank(root,rank)->val;}
    int lower(int v){return loworup(v,0)->val;}
    int upper(int v){return loworup(v,1)->val;}
    void print(){__print(root);}
};

const int MAXN = 200000;

treap<MAXN> w;

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