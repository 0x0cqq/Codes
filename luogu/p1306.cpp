#include <cstdio>
using namespace std;

int gcd(int m,int n){
    while(m!=0&&n!=0){
        m>n?m-=n:n-=m;
    }
    return m+n;
}

int f(int k){
    int last = 0,now = 1;
    if(k == 1){
        return 1;
    }
    else{
        for(int i = 2;i<=k;i++){
            int t = (last+now)%100000000;
            last = now;
            now = t;
        }
    }
    return now;
}

int main(){
    int m,n;
    scanf("%d %d",&m,&n);
    int t = gcd(m,n);
    printf("%d\n",f(t));
    return 0;
}