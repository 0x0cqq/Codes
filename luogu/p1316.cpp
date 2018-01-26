#include <cstdio>
#include <algorithm>
using namespace std;

long long A,B,k[100010];

bool check(long long w){
    //看看间距是不是还可以更大一些
    int b = k[1],num = 1;
    for(int i = 2;i<=A;i++){
        if(k[i]-b>=w){
            num++;
            b = k[i];
        }
    }
    return num>=B;
}

int main(){
    scanf("%lld %lld",&A,&B);
    for(int i = 1;i<=A;i++){
        scanf("%lld",k+i);
    }
    sort(k+1,k+A+1);
    long long b = 0,e = 1000000000000000000;
    while(e-b>1){
        long long t = (b+e)/2;
        if(check(t)) 
            b = t;
        else 
            e = t;
        //printf("b:%d,e:%d,t:%d,check:%d\n",b,e,t,check(t));
    }
    printf("%lld\n",b);
    return 0;
}