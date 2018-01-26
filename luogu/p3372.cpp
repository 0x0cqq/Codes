#include <cstdio>
#define ll long long
using namespace std;

int n,m;

ll sumn[500000],addn[500000];


void maintain(int nown){
    sumn[nown] = sumn[nown<<1] + sumn[nown<<1|1];
}

void build(int nown,int l,int r){
    if(l == r){
        scanf("%lld",&sumn[nown]);
    }
    else{
        addn[nown] = 0;
        int mid = (l+r)>>1;
        build(nown<<1,l,mid);
        build(nown<<1|1,mid+1,r);
        maintain(nown);
    }
}

void add(ll a,int nown,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr){
        addn[nown]+=a;
        sumn[nown]+=(a*(r-l+1));
    }
    else{
        int mid = (l+r)>>1;
        if(addn[nown]!=0){
            addn[nown<<1]+=addn[nown];addn[nown<<1|1]+=addn[nown];
            sumn[nown<<1]+=(addn[nown]*(mid-l+1));
            sumn[nown<<1|1] += (addn[nown]*(r-mid));
            addn[nown] = 0;
        }
        if(ql<=mid)
            add(a,nown<<1,l,mid,ql,qr);
        if(mid+1<=qr)
            add(a,nown<<1|1,mid+1,r,ql,qr);
        maintain(nown);
    }
}

ll query(int nown,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr){
        return sumn[nown];
    }
    else{
        ll ans = 0;
        int mid = (l+r)>>1;
        if(addn[nown]!=0){
            addn[nown<<1]+=addn[nown];addn[nown<<1|1]+=addn[nown];
            sumn[nown<<1]+=(addn[nown]*(mid-l+1));
            sumn[nown<<1|1] += (addn[nown]*(r-mid));
            addn[nown] = 0;
        }
        if(ql<=mid)
            ans += query(nown<<1,l,mid,ql,qr);
        if(qr>=mid+1)
            ans += query(nown<<1|1,mid+1,r,ql,qr);
        return ans;
    }
}

int main(){
    scanf("%d %d",&n,&m);
    build(1,1,n);
    for(int i = 1;i<=m;i++){
        int f;
        scanf("%d",&f);
        if(f == 1){
            int a,b,c;
            scanf("%d %d %d",&a,&b,&c);
            add(c,1,1,n,a,b);
        }
        else{
            int a,b;
            scanf("%d %d",&a,&b);
            long long ans = query(1,1,n,a,b);
            printf("%lld\n",ans);
        }
    }
    return 0;
}