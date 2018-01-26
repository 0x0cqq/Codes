#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int y[20],n,s[20],sum;
bool flag = 0;

void yanghui(int num){
    y[0] = 1;
    for(int i = 1;i<num;i++)
        for(int j = i;j>=0;j--)
            y[j] += y[j-1];
}


void dfs(int now,int ans){
    //printf("?%d %d\n",now,ans);
    if(now == n){
        if(ans==sum){
            for(int i = 0;i<n;i++)
                printf("%d ",s[i]);
            putchar('\n');
            flag = 1;
        }
        return;
    }
    if(flag||ans>sum)
        return;
    for(int i = 1;i<=n;i++){
        //printf("l ");
        bool f = 0;
        for(int j = 0;j<now;j++)
            if(s[j] == i){
                f = 1;
            }
        if(f)
            continue;
        s[now] = i;
        //for(int i = 0;i<n;i++)
        //    printf("%d ",s[i]);
        //putchar('\n');
        dfs(now+1,ans+i*y[now]);
        if(flag)
            return;
        s[now] = 0;
    }
}

int main(){
    scanf("%d %d",&n,&sum);
    yanghui(n);
    //for(int i = 0;i<n;i++){
    //   printf("%d ",y[i]);
    //}
    //putchar('\n');
    dfs(0,0);
    return 0;
}