#include <cstdio>
#include <cstdlib>
#define ll long long
#define lson (nown<<1)
#define rson (nown<<1|1)
#define mid ((l+r)>>1)
using namespace std;

int n,m;

int addn[500000],chengn[500000],sumn[500000];

inline ll qr(){
    ll f = 1,s = 0;char ch = getchar();
    while(ch<='0'||ch>'9'){
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

void push_down(int nown,int l,int r){
    if(addn[nown] !=0){
        addn[lson] += addn[nown];  addn[rson] += addn[nown];
        sumn[lson] += addn[nown]*(mid-l+1);
        sumn[rson] += addn[nown]*(r-mid);
        addn[nown] = 0;
    }
}

void push_up(int nown){
    sumn[nown] = sumn[lson] + sumn[rson];
}

void build(int nown,int l,int r){
    addn[nown] = 0;
    chengn[nown] = 1; 
    if(l == r){
        sumn[nown] = qr();
    }
    else{
        build(lson,l,mid);
        build(rson,mid+1,r);
        push_up(nown);
    }
}

int query(int nown,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr)
        return sumn[nown];
    else{
        push_down(nown,l,r);
        ll res = 0;
        if(ql<=mid) res+=query(lson,l,mid,ql,qr);
        if(mid+1<=qr) res+=query(rson,mid+1,r,ql,qr);
        return res;
    }
}

void add(int val,int nown,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr){
        addn[nown]+=val;sumn[nown]+=(val*(r-l+1));
    }
    else{
        push_down(nown,l,r);
        if(ql<=mid) add(val,lson,l,mid,ql,qr);
        if(mid+1<=qr) add(val,rson,mid+1,r,ql,qr);
        push_up(nown);
    }
}


int main(){
    scanf("%d %d",&n,&m);
    int last = 0;
    for(int i = 1;i<=n;i++){
        int t;scanf("%d",&t);
        add(t-last,1,1,n,i,i);
        last = t;
    }
    for(int i = 0;i<m;i++){
        int f,a,b,k,d;
        scanf("%d",&f);
        switch(f){
            case 1:
                scanf("%d %d %d %d",&a,&b,&k,&d);
                add(d,1,1,n,a+1,b);
                add(k,1,1,n,a,a);
                add(-(b-a)*d-k,1,1,n,b+1,b+1);
                break;
            case 2:
                scanf("%d",&a);
                printf("%d\n",query(1,1,n,1,a));
                break;
        }
    }
    return 0;
}