#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
#define For(i,a,b) for(i=(a),i<=(b);++i)
#define Forward(i,a,b) for(i=(a),i>=(b);--i)
template<typename T>inline void read(T &x)
{
    T f=1;x=0;char c;
    for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
    for(;isdigit(c);c=getchar())x=x*10+(c^48);
    x*=f;
}
using namespace std;

const int MAXN=1e5+7;

static int n,m;

static struct juice
{
    int d;
    long long p,l;
}p[MAXN];

inline bool cmp1(juice a,juice b){return a.d<b.d;}

static struct boy
{
    long long g,l;
    int id;
}q[MAXN],ret[MAXN];

inline bool cmp2(boy a,boy b){return a.g<b.g;}

inline void init()
{
    read(n);read(m);
    Rep(i,1,n)read(p[i].d),read(p[i].p),read(p[i].l);
    p[n+1].d=-1;p[n+1].p=0;p[n+1].l=1e18;++n;
    sort(p+1,p+n+1,cmp1);
    Rep(i,1,m)read(q[i].g),read(q[i].l),q[i].id=i;
}

static int ans[MAXN],pos;

typedef pair<long long,int>Pr;

static multiset<Pr>K;

static multiset<Pr>::iterator it;

void div(int l,int r,int x,int y)
{
    if(x>y)return;
    if(l==r){Rep(i,x,y)ans[q[i].id]=p[l].d;return;}
    static int mid,lp,rp;mid=(l+r)>>1,lp=x,rp=y;
    static long long sm,cost;sm=0,cost=0;
    sort(q+x,q+y+1,cmp2);
    while(pos>mid+1)--pos,K.insert(Pr(p[pos].p,p[pos].l));
    while(pos<mid+1)K.erase(K.lower_bound(Pr(p[pos].p,p[pos].l)))
        ,++pos;
    it=K.begin();
    Rep(i,x,y)
    {
        while(it!=K.end()&&cost+it->first*it->second<=q[i].g)
            cost+=it->first*it->second,sm+=it->second,++it;
        //cerr<<sm<<' '<<cost<<' '<<q[i].l<<' '<<q[i].g<<endl;
        if(q[i].l<=sm||(it!=K.end()
            &&sm+(q[i].g-cost)/it->first>=q[i].l))
                ret[rp--]=q[i];
        else ret[lp++]=q[i];
    }
    Rep(i,x,y)q[i]=ret[i];
    div(mid+1,r,lp,y);
    div(l,mid,x,lp-1);
}

inline void solve()
{
    pos=n+1;div(1,n,1,m);
    Rep(i,1,m)printf("%d\n",ans[i]);
}

int main()
{
    init();
    solve();
    //cerr<<1.0*clock()/CLOCKS_PER_SEC<<endl;
    return 0;
}