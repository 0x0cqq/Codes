#include <bits/stdc++.h>
using namespace std;


const int MAXN = 1100000;

int n,m;
int num[MAXN], dp[MAXN];

deque<int> q;// 其中的int为pos

void init(){
    scanf("%d",&n);
    num[0] = 0x3f3f3f3f;
    for(int i = 1;i<=n;i++)
        scanf("%d",&num[i]);
}


bool cmp(int x,int y){// 1 -> x 的优先级大于y 0 -> y的优先级大于x
    if(dp[x]!=dp[y])
        return dp[x] < dp[y];
    return num[x] > num[y];
}

int getans(int k){
    dp[1] = 0;
    while(!q.empty()) q.pop_back();
    q.push_back(1);
    for(int i = 2;i<=n;i++){
        while(!q.empty() && q.front() < i-k)
            q.pop_front();
        // printf("i:%d %d %d\n", i, k, q.front());
        // for(auto w:q){
        //     printf("%d ",w);
        // }
        // printf("\n");
        dp[i] = dp[q.front()] + ((num[q.front()] > num[i])? 0: 1);
        while(!q.empty() && cmp(i,q.back()))
            q.pop_back();
        q.push_back(i);
    }
    // for(int i = 1;i<=n;i++){
    //     printf("%d:%d\n",i,dp[i]);
    // }
    return dp[n];
}

void solve(){
    scanf("%d",&m);
    int t;
    for(int i = 1;i<=m;i++){
        scanf("%d",&t);
        printf("%d\n",getans(t));
    }
}

int main(){
    init();
    solve();
    return 0;
}