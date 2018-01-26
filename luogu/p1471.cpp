#include <cstdio>
#define ld double
#define lson (nown<<1)
#define rson ((nown<<1)|1)
#define s(x) ((x)*(x))
#define mid ((l+r)>>1)
using namespace std;

int n,m;

ld add[500000],sum1[500000],sum2[500000];

void push_up(int nown){
    sum1[nown] = sum1[lson]+sum1[rson];
    sum2[nown] = sum2[lson]+sum2[rson];
}

void push_down(int nown,int l,int r){
    if(add[nown]!=0){
        sum2[lson] += 2*sum1[lson]*add[nown]+s(add[nown])*(mid-l+1);
        sum2[rson] += 2*sum1[rson]*add[nown]+s(add[nown])*(r-mid);
        sum1[lson] += add[nown]*(mid-l+1);sum1[rson]+=add[nown]*(r-mid);
        add[lson] += add[nown];add[rson] += add[nown];
        add[nown] = 0;
    }
}

void build(int nown,int l,int r){
    if(l == r){
        scanf("%lf",&sum1[nown]);
        sum2[nown] = s(sum1[nown]);
        return;
    }
    add[nown] = 0;
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(nown);
    return;
}


void ad(ld num,int ql,int qr,int nown,int l,int r){
    if(ql<=l&&r<=qr){
        sum2[nown] += 2*sum1[nown]*num+s(num)*(r-l+1);
        sum1[nown] += num*(r-l+1);
        add[nown] += num;
        return;
    }
    push_down(nown,l,r);
    if(ql<=mid)
        ad(num,ql,qr,lson,l,mid);
    if(qr>=mid+1)
        ad(num,ql,qr,rson,mid+1,r);
    push_up(nown);
}

ld query(bool w,int ql,int qr,int nown,int l,int r){//w == 0,sum1;w == 1,sum2
    ld res = 0;
    if(ql<=l&&r<=qr){
        if(w)
            return sum2[nown];
        else
            return sum1[nown];
    }
    push_down(nown,l,r);
    if(ql<=mid)
        res += query(w,ql,qr,lson,l,mid);
    if(qr>=mid+1)
        res += query(w,ql,qr,rson,mid+1,r);
    return res;
}

int main(){
    scanf("%d %d",&n,&m);
    build(1,1,n);
    for(int i = 0;i<m;i++){
        ld w,x,y,k;
        scanf("%lf %lf %lf",&w,&x,&y);
        if(w == 1){
            scanf("%lf",&k);
            ad(k,x,y,1,1,n);
        }
        else if(w == 2){
            ld tmp = query(0,x,y,1,1,n)/(y-x+1);
            printf("%.4lf\n",tmp); 
        }
        else if(w == 3){
            ld tmp1 = query(0,x,y,1,1,n);
            ld tmp2 = query(1,x,y,1,1,n);
            ld a = (tmp2 - (s(tmp1)/(y-x+1)))/(y-x+1);
            printf("%.4lf\n",a);
        }
    }
    return 0;
}