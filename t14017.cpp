#include <cstdio>
#include <cmath>
using namespace std;

long long c[100005];

unsigned long long mod(int k,int n,int p){
    if(n==1)
        return k%p;
    else if(n&1){
        unsigned long long x = mod(k,n/2,p);
        return (x*((x*k)%p))%p;
    }
    else{
        unsigned long long x = mod(k,n/2,p);
        return (x*x)%p;
    }
}


int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i = 1;i<=n;i++)
        scanf("%lld",&(c[i]));
    for(int i = 1;i<=m;i++){
        int a,l,r,xp;
        scanf("%d %d %d %d",&a,&l,&r,&xp);
        if(a==1){
            for(int i = l;i<=r;i++){
                c[i]+=xp;
            }
        }
        else if(a==2){
            long long ans = 1;
            for(int i = r;i>=l;i--){
                ans = mod(c[i],ans,xp);
            }
            printf("%lld\n",ans);
        }
    }
    return 0;
}