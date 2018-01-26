#include <cstdio>
using namespace std;

bool gcd(int a,int b){
    while(a!=0&&b!=0){
        if(a>=b)
            a-=b;
        else
            b-=a;
    }
    return a+b == 1;
}

int main(){
    int x,y,ans = 0;
    scanf("%d %d",&x,&y);
    if(y%x==0){
        int t = y/x;
        for(int i = 1;i<=t;i++)
            ans+= (t%i == 0&&gcd(t/i,i));
    }
    printf("%d\n",ans);
    return 0;
}