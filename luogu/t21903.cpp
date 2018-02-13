#include <cstdio>
using namespace std;


int main(){
    int t;
    scanf("%d\n",&t);
    for(int i = 1;i<=t;i++){
        int n,a,b;
        scanf("%d %d %d",&n,&a,&b);
        if(a == 0 ||(b!=0 &&(n>a)&&(n%a)/b<=n/a+1)){
            printf("Yes\n");
        }
        else{
            printf("No\n");
        }
    }
    return 0;
}