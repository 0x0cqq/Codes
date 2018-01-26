#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int n,ans = 0;
int a[40000];


int gcd(int a,int b){
    while(a!=0&&b!=0){
        if(b>a)
            b-=a;
        else
            a-=b;
    }
    return a+b;
}

int solve(int now){
    for(int i = 2;i<=now;i++){
        if(now%i == 0){
            if((now/i)%i==0)
                return solve(now/i)*i;
            else
                return solve(now/i)*(i-1);
        }
    }
    return 0;
}

int main(){
    //freopen("1.txt","w",stdout);

    scanf("%d",&n);
    if(n == 1){
        printf("0");
        return 0;
    }
    for(int k = 1;k<n;k++){
        ans+=solve(k);
    }
    printf("%d\n",ans+2);
    return 0;
}