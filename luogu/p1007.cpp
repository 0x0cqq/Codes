#include <cstdio>
#include <algorithm>
using namespace std;

int main(){
    int l,n,maxn = 0,minn = 0;
    scanf("%d %d",&l,&n);
    for(int i = 0;i<n;i++){
        int t;
        scanf("%d",&t);
        minn = max(minn,min(t,l+1-t));
        maxn = max(maxn,max(t,l+1-t));
    }
    printf("%d %d\n",minn,maxn);
    return 0;
}