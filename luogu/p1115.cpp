#include <cstdio>
using namespace std;

int main(){
    int n,minn = 0,maxn = -100000000;
    scanf("%d",&n);
    int last = 0,t;
    while(n--){
        scanf("%d",&t);
        t = last+t;
        maxn = maxn>t-minn?maxn:t-minn;
        minn = minn<t?minn:t;
        last = t;
    }
    printf("%d\n",maxn);
    return 0;
}