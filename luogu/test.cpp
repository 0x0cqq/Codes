#include <iostream>
#include <cstdio>
#include <cmath>
#include <unistd.h>
using namespace std;
long long a[2000005],t[2000055],ans[2000005];
long long n,m;
long long make_l(long long x){
    return x<<1;
}
long long make_r(long long x){
    return x<<1|1;
}
long long push_sum(long long x){
    ans[x]=ans[make_l(x)]+ans[make_r(x)];
}
void build_tree(long long x,long long l,long long r){
    if(l==r){
        ans[x]=a[l];
        return;
    }
    long long mid=(l+r)>>1;
    build_tree(make_l(x),l,mid);
    build_tree(make_r(x),mid+1,r);
    push_sum(x);
}
void f(long long p,long long l,long long r,long long num){
    t[p]+=num;
    ans[p]+=num*(r-l+1);
}
void down(long long x,long long l,long long r){
    long long mid=(l+r)>>1;
    if(t[x]){
        f(make_l(x),l,mid,t[x]);
        f(make_r(x),mid+1,r,t[x]);
        t[x]=0;
    }
}
void update(long long al,long long ar,long long l,long long r,long long p,long long k){
    if(al<=l&&r<=ar){
        ans[p]+=k*(r-l+1);
        t[p]+=k;
        return;
    }
    down(p,l,r);
    long long mid=(l+r)>>1;
    if(al<=mid)
        update(al,ar,l,mid,make_l(p),k);
    if(ar>mid)
        update(al,ar,mid+1,r,make_r(p),k);
    push_sum(p);
}
long long fin(long long x,long long y,long long l,long long r,long long p){
        long long sum=0;
        printf("x,y:%lld %lld l,r:%lld %lld p:%lld\n",x,y,l,r,p);
        usleep(1000000);
        if(x<=l&&r<=y)
            return ans[p];
        else{
            long long mid=(l+r)>>1;
            //down(p,l,r);
            if(x<=mid)
                sum+=fin(x,y,l,mid,make_l(p));
            if(y>mid)
                sum+=fin(x,y,mid+1,r,make_r(p));
            return sum;
        }
}

int main(){
   cin>>n>>m;
   for(int i=1;i<=n;i++){
       scanf("%lld%lld",&n,&m);
   }
   build_tree(1,1,n);
   for(int i=1;i<=m;i++)
   {
       long long  wzx;
       scanf("%lld",&wzx);
       if(wzx==1)
       {
           long long b,c,d;
           scanf("%lld%lld%lld",&b,&c,&d);
           update(b,c,1,n,1,d);
       }
       else
       {
           long long b,c;
           scanf("%lld%lld",&b,&c);
           printf("n:%lld\n",n);
           printf("%lld\n",fin(b,c,1,n,1));
       }
   }
   return 0;
}