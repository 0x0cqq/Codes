#include <cstdio>
#include <cmath>
using namespace std;

int main(){
    char a[1000];
    int n,m,i = 0;
    scanf("%d %d",&n,&m);
    int t = n;
    while(t!=0){
        int yushu;
        for(yushu = 0;;yushu++)
            if((t-yushu)%m == 0)
                break;
        if(0<=yushu&&yushu<=9)
            a[i++] = yushu + 48;
        else if(yushu>=10)
            a[i++] = yushu + 55;
        t = (t-yushu)/m;
    }
    printf("%d=",n);
    while(i>0)
        putchar(a[--i]);
    printf("(base%d)\n",m);
    return 0;
}