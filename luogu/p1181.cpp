#include <cstdio>
using namespace std;


int main(){
    int n,m,now = 0,ans = 0;
    scanf("%d %d",&n,&m);
    for(int i = 0;i<n;i++){
        int t;
        scanf("%d",&t);
        now+=t;
        if(now>m){
            ans++;
            now = t;
        }
        if(i == n-1)
            ans++;
    }
    printf("%d\n",ans);
    return 0;
}