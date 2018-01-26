#include <cstdio>
using namespace std;

int num[10],n;

void dfs(int now){
    if(now == n){
        for(int i = 0;i<n;i++){
            printf("%5d",num[i]);
        }
        putchar('\n');
        return;
    }
    else{
        for(int i = 1;i<=n;i++){
            int f = 1;
            for(int j = 0;j<now;j++){
                if(num[j]==i){
                    f = 0;
                    break;
                }
            }
            if(!f)
                continue;
            else{
                num[now] = i;
                dfs(now+1);
                num[now] = 0;
            }
        }
    }
}

int main(){
    scanf("%d",&n);
    dfs(0);
    return 0;
}