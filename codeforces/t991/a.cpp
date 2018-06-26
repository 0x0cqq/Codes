#include <cstdio>
#include <algorithm>
using namespace std;


int main(){
    int a,b,c,n;
    scanf("%d %d %d %d",&a,&b,&c,&n);
    int k = n-((a+b)-c);
    if(k <= 0 || (c > a+b) || c > min(a,b))
        printf("-1\n");
    else{
        printf("%d\n",k);
    }
    return 0;
}