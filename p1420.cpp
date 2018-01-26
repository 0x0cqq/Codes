#include <cstdio>
using namespace std;

int main(){
    int n,last = -1,max = 0,now = 0;
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        int t;
        scanf("%d",&t);
        if(t-last!=1){
            if(now>max) max = now;
            now = 1;
        }
        else{
            now++;
            if(i == n-1&&now>max) max = now;
        }
        last = t;
    }
    printf("%d\n",max);
    return 0;
}