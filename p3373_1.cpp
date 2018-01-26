#include <cstdio>
#define LL long long
#define L(x) x<<1    //左儿子 x*2 
#define R(x) x<<1|1 //右儿子  x*2+1
const int maxn =1e5+5;
using namespace std;
LL n,m,modd,num[maxn];
inline LL read() {
    LL x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
    return x*f;
}
struct T {
    LL l,r;
    LL sum,add,mul;
} tree[maxn<<2];//注意开long long 和四倍空间 
inline void update(LL p) {
    tree[p].sum=tree[L(p)].sum+tree[R(p)].sum;
    return;
}
inline void spread(LL p) {
    LL mid=(tree[p].l+tree[p].r)>>1;
    if(tree[p].mul!=1) {
        tree[L(p)].mul=tree[L(p)].mul*tree[p].mul%modd;
        tree[R(p)].mul=tree[R(p)].mul*tree[p].mul%modd;
        tree[L(p)].add=tree[L(p)].add*tree[p].mul%modd;
        tree[R(p)].add=tree[R(p)].add*tree[p].mul%modd;
        tree[L(p)].sum=tree[L(p)].sum*tree[p].mul%modd;
        tree[R(p)].sum=tree[R(p)].sum*tree[p].mul%modd;
        tree[p].mul=1;
    }
    if(tree[p].add) {
        tree[L(p)].add=(tree[L(p)].add+tree[p].add)%modd;
        tree[R(p)].add=(tree[R(p)].add+tree[p].add)%modd;
        tree[L(p)].sum=(tree[L(p)].sum+tree[p].add*(mid-tree[p].l+1)%modd)%modd;
        tree[R(p)].sum=(tree[R(p)].sum+tree[p].add*(tree[p].r-mid)%modd)%modd;//tree[p].r-mid不加1 
        tree[p].add=0;
    }
    return;
}
inline void build(LL l,LL r,LL p) {//建树 
    tree[p].l=l,tree[p].r=r,tree[p].mul=1;
    if(l==r) {
        tree[p].sum=num[l];
        tree[p].mul=1;
        return;
    }
    LL mid=(tree[p].l+tree[p].r)>>1;
    build(l,mid,L(p));
    build(mid+1,r,R(p));
    update(p);
    return;
}
inline void change1(LL l,LL r,LL p,LL v) {//区间增值 
    if(tree[p].l==l&&tree[p].r==r) {
        tree[p].add=(tree[p].add+v);
        tree[p].sum=(tree[p].sum+v*(r-l+1));
        return;
    }
    spread(p);
    LL mid=(tree[p].l+tree[p].r)>>1;
    if(r<=mid) change1(l,r,L(p),v);
    else if(l>mid) change1(l,r,R(p),v);
    else change1(l,mid,L(p),v),change1(mid+1,r,R(p),v);
    update(p);
    return;
}
inline void change2(LL l,LL r,LL p,LL v) {//区间乘法 
    if(tree[p].l==l&&tree[p].r==r) {
        tree[p].add=(tree[p].add*v)%modd;//标记也要乘上v 
        tree[p].sum=(tree[p].sum*v)%modd;
        tree[p].mul=(tree[p].mul*v)%modd;
        return;
    }
    spread(p);
    LL mid=(tree[p].l+tree[p].r)>>1;
    if(r<=mid) change2(l,r,L(p),v);
    else if(l>mid) change2(l,r,R(p),v);
    else change2(l,mid,L(p),v),change2(mid+1,r,R(p),v);
    update(p);
    return;
}
inline LL ask_sum(LL l,LL r,LL p) {
    if(tree[p].l==l&&tree[p].r==r) {
        return tree[p].sum;
    }
    spread(p);
    LL mid=(tree[p].l+tree[p].r)>>1;
    if(r<=mid) return ask_sum(l,r,L(p));
    else if(l>mid) return ask_sum(l,r,R(p));
    else  return ask_sum(l,mid,L(p))+ask_sum(mid+1,r,R(p));
}
LL opt,l,r,v;
int main() {
    n=read(),m=read(),modd=read();
    for(int i=1; i<=n; i++) num[i]=read();
    build(1,n,1);
    while(m--) {
        opt=read();
        if(opt==1) {
            l=read(),r=read(),v=read();
            change2(l,r,1,v);
        }
        if(opt==2) {
            l=read(),r=read(),v=read();
            change1(l,r,1,v);
        }
        if(opt==3) {
            l=read(),r=read();
            printf("%lld\n",ask_sum(l,r,1)%modd);
        }
    }
    return 0;
}