#include <cstdio>
using namespace std;

int n,t,now = 0,ans = 0;

int main(){
    scanf("%d %d",&n,&t);
    for(int i = 0;i<n;i++){
        int tem;
        scanf("%d",&tem);
        if(tem<=now){
            ans+=t-(now-tem+1);
            now = tem+t-1;
        }
        else{
            ans+=t;
            now = tem+t-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}