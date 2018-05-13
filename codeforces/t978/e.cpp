#include <cstdio>
#include <algorithm>
using namespace std;

int minn = 0,maxn = 0;

int n,w;

int main(){
    scanf("%d %d",&n,&w);
    int tmp = 0,tot = 0;
    for(int i = 1;i<=n;i++){
        scanf("%d",&tmp);
        tot += tmp;
        minn = min(tot,minn);
        maxn = max(tot,maxn);
    }
    int ans = w - maxn + minn+1;
    if(ans > 0)
        printf("%d\n",w - maxn + minn+1);
    else{
        printf("%d\n",0);
    }
    return 0;
}