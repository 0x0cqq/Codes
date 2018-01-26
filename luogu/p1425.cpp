#include <cstdio>
using namespace std;

int main(){
    int a,b,c,d;
    scanf("%d %d %d %d",&a,&b,&c,&d);
    int res1,res2;
    res1 = c-a;
    res2 = d-b;
    if(res2<0){
        res1--;
        res2+=60;
    }
    printf("%d %d\n",res1,res2);
    return 0;
}