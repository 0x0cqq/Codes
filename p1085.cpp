#include <cstdio>
using namespace std;

int main(){
    int maxn = 0,m = 0;
    for(int i = 1;i<=7;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        if(a+b-8>m){
            maxn = i;
            m = a+b-8;
        }
    }
    printf("%d\n",maxn);
    return 0;
}