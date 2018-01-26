#include <cstdio>
using namespace std;

long long a[1005][1005],R,w[1005][1005];

long long cal(long long k,long long n){
    if(k==1) return a[1][1];
    else{
        if(w[k][n]!=-1)
            return w[k][n];
        else{
            if(n==1)
                return w[k][n] = cal(k-1,n)+a[k][n];
            else if(n==k)
                return w[k][n] = cal(k-1,n-1)+a[k][n];
            else if(cal(k-1,n)>cal(k-1,n-1))
                return w[k][n] = cal(k-1,n)+a[k][n];
            else
                return w[k][n] = cal(k-1,n-1)+a[k][n];
        }
    }
}


int main(){
    scanf("%lld",&R);
    for(int i = 1;i<=R;i++){
        for(int k = 1;k<=i;k++){
            scanf("%lld",&(a[i][k]));
            w[i][k] = -1;
        }
    }
    long long max = 0;
    for(int i = 1;i<=R;i++){
        int t = cal(R,i);
        if(t>max){
            max = t;
        }
    }
    printf("%lld\n",max);
    return 0;
}