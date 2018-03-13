#include <cstdio>
#define ll long long
#define lson (nown<<1)
#define rson (nown<<1|1)
#define mid ((l+r)>>1)
#pragma GCC optimize(2)
using namespace std;

ll addn[500000],chengn[500000],sumn[500000];
ll n,m,p;

inline ll qr(){
    ll f = 1,s = 0;char ch = getchar();
    while(ch<'0'||ch>'9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9'){
        s = (s<<3)+(s<<1)+ch-48;
        ch = getchar();
    }
    return f*s;
}

void pushup(int nown){
    sumn[nown] = (sumn[lson]+sumn[rson])%p;
}

void pushdown(int nown,int l,int r){
    if(chengn[nown]!=1){
        chengn[lson]*=chengn[nown];chengn[rson]*=chengn[nown];
        addn[lson]*=chengn[nown];addn[rson]*=chengn[nown];
        sumn[lson]*=chengn[nown];sumn[rson]*=chengn[nown];
        chengn[nown] = 1;
    }
    if(addn[nown]!=0){
        addn[lson] += addn[nown];addn[rson] += addn[nown];
        sumn[lson] += addn[nown]*(mid-l+1);
        sumn[rson] += addn[nown]*(r-mid);
        addn[nown] = 0;
    }
    chengn[lson]%=p;chengn[rson]%=p;
    addn[lson]%=p;addn[rson]%=p;
    sumn[lson]%=p;sumn[rson]%=p;
}

void build(int nown,int l,int r){
    addn[nown] = 0;chengn[nown] = 1;
    if(l == r){
        sumn[nown] = qr()%p;
        return;
    }
    build(lson,l,mid);
    build(rson,mid+1,r);
    pushup(nown);
}

void update(ll val,int nown,int l,int r,int ql,int qr,bool optn){
    if(l>qr||r<ql)
        return;
    if(ql<=l&&r<=qr){
        if(optn){
            addn[nown]+= val;
            sumn[nown]+= val*(r-l+1);
        }
        else{
            addn[nown]*=val;chengn[nown]*=val;
            sumn[nown]*=val;
        }
        chengn[nown]%=p;addn[nown]%=p;sumn[nown]%=p;
        return;
    }
    pushdown(nown,l,r);
    if(ql<=mid)
        update(val,lson,l,mid,ql,qr,optn);
    if(mid+1<=qr)
        update(val,rson,mid+1,r,ql,qr,optn);
    pushup(nown);
}

ll query(int nown,int l,int r,int ql,int qr){
    if(l>qr||r<ql)
        return 0;
    if(ql<=l&&r<=qr){
        return sumn[nown]%p;
    }
    pushdown(nown,l,r);
    ll ans = 0;
    if(ql<=mid)
        ans+=query(lson,l,mid,ql,qr);
    if(mid+1<=qr)
        ans+=query(rson,mid+1,r,ql,qr);
    return ans%p;
}


int main(){
    scanf("%lld %lld",&n,&p);
    build(1,1,n);
    scanf("%lld",&m);
    for(int i = 0;i<m;i++){
        ll a,b,c,d;
        a = qr();
        if(a == 1){
            b =qr();c = qr();d = qr();
            update(d,1,1,n,b,c,0);
        }
        else if(a == 2){
            b =qr();c = qr();d = qr();
            update(d,1,1,n,b,c,1);
        }
        else if(a == 3){
            b = qr();c = qr();
            printf("%lld\n",query(1,1,n,b,c));
        }
    }
    return 0;
}