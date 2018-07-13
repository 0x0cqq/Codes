#include <bits/stdc++.h>
#define INF 2147483647
using namespace std;

const int MAXN = 51000;
namespace Treap{
int val[MAXN*40],p[MAXN*40],siz[MAXN*40],cnt[MAXN*40];
int c[MAXN*40][2],treapcnt = 0;
void update(int x){
    if(!x) return;
    siz[x] = siz[c[x][0]] + siz[c[x][1]] + cnt[x];
}
int newnode(int v){
    int x = ++treapcnt;
    c[x][0]=c[x][1] = 0;
    siz[x]=cnt[x]=1;val[x] = v;
    p[x] = rand();
    return x;
}
void init(){
    p[0] = 2147483647;
    siz[0] = cnt[0] = 0;
    val[0] = 2147483647;
}
int newtree(){
    int x = newnode(-INF),y = newnode(INF);
    siz[x] = siz[y] = cnt[x] = cnt[y] = 1;
    p[x] = 2,p[y] = 1;
    c[y][0] = x;
    update(y);
    return y;
}
void rotate(int &x,int t){
    int y = c[x][t];
    c[x][t] = c[y][1-t];
    c[y][1-t] = x;
    update(x),update(y);
    x = y;
}
void __insert(int &x,int v){
    if(x){
        if(v == val[x])
            cnt[x]++;
        else{
            int t = v > val[x];
            __insert(c[x][t],v);
            if(p[c[x][t]] < p[x])
                rotate(x,t);
        }
    }
    else{
        x = newnode(v);
    }
    update(x);
}
void __erase(int &x,int v){
    if(val[x] == v){
        if(cnt[x] > 1){
            cnt[x]--;
        }
        else{
            if(!c[x][0]&&!c[x][1]){
                x = 0;return;
            }
            int t = p[c[x][0]] > p[c[x][1]];
            rotate(x,t);
            __erase(x,v);
        }
    }
    else{
        __erase(c[x][val[x] < v],v);
    }
    update(x);
}
int getkth(int x,int k){//1->n
    if(!x) return 0;
    if(k <= siz[c[x][0]])
        return getkth(c[x][0],k);
    else if(k <= siz[c[x][0]] + cnt[x])
        return val[x];
    else
        return getkth(c[x][1],k - siz[c[x][0]] - cnt[x]);
}
int getrank(int x,int v){
    if(!x) return -1;
    if(v < val[x])
        return getrank(c[x][0],v);
    else if(v == val[x])
        return siz[c[x][0]]-1;
    else
        return siz[c[x][0]] + cnt[x] + getrank(c[x][1],v);
}
void print(int x,int depth = 0){
    if(depth == 0) printf("root:%d----------------------\n",x);
    if(!x) return;
    print(c[x][0],depth+1);
    for(int i = 0;i<depth;i++) putchar(' ');
    printf("x:%d val:%d siz:%d cnt:%d c:%d %d p:%d\n",x,val[x],siz[x],cnt[x],c[x][0],c[x][1],p[x]);
    print(c[x][1],depth+1);
    if(depth == 0) printf("----------------------------\n");
}
}

namespace SegTree{
int tree[MAXN*5];
#define lson (nown<<1)
#define rson (nown<<1|1)
#define mid ((l+r)>>1)
void build(int nown,int l,int r,int *num){
    tree[nown] = Treap::newtree();
    for(int i = l;i<=r;i++)
        Treap::__insert(tree[nown],num[i]);
    //Treap::print(tree[nown]);
    if(l == r) return;
    build(lson,l,mid,num);
    build(rson,mid+1,r,num);
}
void print(int nown,int l,int r){
    Treap::print(tree[nown]);
    if(l == r) return;
    print(lson,l,mid);
    print(rson,mid+1,r);
}
int getrank(int nown,int l,int r,int ql,int qr,int v){
    if(ql <= l && r <= qr){
        return Treap::getrank(tree[nown],v);
    }
    else{
        int ans = 0;
        if(ql <= mid)
            ans += getrank(lson,l,mid,ql,qr,v);
        if(qr >= mid+1)
            ans += getrank(rson,mid+1,r,ql,qr,v);
        return ans;
    }
}
void update(int nown,int l,int r,int pos,int last,int now){
    Treap::__erase(tree[nown],last);
    Treap::__insert(tree[nown],now);
    if(l == r) return;
    if(pos <= mid)
        update(lson,l,mid,pos,last,now);
    else
        update(rson,mid+1,r,pos,last,now);
}
int lower(int nown,int l,int r,int ql,int qr,int v){
    if(ql <= l && r <= qr){
        //printf("l:%d r:%d v:%d ans:%d\n", l,r,v,Treap::getkth(tree[nown],Treap::getrank(tree[nown],v)+1));
        return Treap::getkth(tree[nown],Treap::getrank(tree[nown],v)+1);
    }
    else{
        int ans = -INF;
        if(ql <= mid)
            ans = max(ans,lower(lson,l,mid,ql,qr,v));
        if(mid+1 <= qr)
            ans = max(ans,lower(rson,mid+1,r,ql,qr,v));
        return ans;
    }
}
int upper(int nown,int l,int r,int ql,int qr,int v){
    if(ql <= l && r <= qr){
        //printf("l:%d r:%d v:%d tmp:%d ans:%d\n", l,r,v,Treap::getrank(tree[nown],v+1),Treap::getkth(tree[nown],Treap::getrank(tree[nown],v+1)+2));
        return Treap::getkth(tree[nown],Treap::getrank(tree[nown],v+1)+2);
    }
    else{
        int ans = INF;
        if(ql <= mid)
            ans = min(ans,upper(lson,l,mid,ql,qr,v));
        if(mid+1 <= qr)
            ans = min(ans,upper(rson,mid+1,r,ql,qr,v));
        return ans;
    }
}
}

int n,m;
int num[MAXN];

int getrank(int l,int r,int v){
    return SegTree::getrank(1,1,n,l,r,v)+1;
}

int getkth(int l,int r,int k){
    int b = 0,e = INF;
    while(b!=e){
        int m = (b+e)>>1;
        int t = getrank(l,r,m+1)-1;
        //printf("b:%d e:%d m:%d ANS:%d\n",b,e,m,t);
        //usleep(100000);
        if(t >= k) e = m;
        else b = m+1;
    }
    return b;
}

void update(int pos,int val){
    SegTree::update(1,1,n,pos,num[pos],val);
    num[pos] = val;
}

int lower(int l,int r,int v){
    return SegTree::lower(1,1,n,l,r,v);
}

int upper(int l,int r,int v){
    return SegTree::upper(1,1,n,l,r,v);
}

//------------------------------

void init(){
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++){
        scanf("%d",&num[i]);
    }
}

void build(){
    Treap::init();
    SegTree::build(1,1,n,num);
}

void solve(){
    int op,l,r,k;
    for(int i = 1;i<=m;i++){
        scanf("%d %d %d",&op,&l,&r);
        if(op != 3) scanf("%d",&k);
        if(op == 1)
            printf("%d\n",getrank(l,r,k));
        else if(op == 2)
            printf("%d\n",getkth(l,r,k));
        else if(op == 3)
            update(l,r);
        else if(op == 4)
            printf("%d\n",lower(l,r,k));
        else if(op == 5)
            printf("%d\n",upper(l,r,k));
        //SegTree::print(1,1,n);
    }
}

int main(){
    init();
    build();
    solve();
    return 0;
}