#include <cstdio>
using namespace std;
#define ll long long

ll d;
int ci[10],q[10];

ll jiecheng[20];

ll dfs(int nowpos){
    if(nowpos == 10){
        ll ans = 0;
        int sum = 0;
        for(int i = 0;i<10;i++)
            sum += q[i];
        ans = jiecheng[sum];
        // printf("%lld\n",ans);
        for(int i = 0;i<10;i++){
            if(q[i]){
                ans /= jiecheng[q[i]];
            }
        }
        if(q[0]){
            ll t = jiecheng[sum-1];
            q[0]--;
            for(int i = 0;i<10;i++){
                if(q[i]){
                    t /= jiecheng[q[i]];
                }            
            }
            q[0]++;
            ans -= t;
        }
        return ans;
    }
    else if(ci[nowpos] == 0){
        return dfs(nowpos+1);
    }
    else{
        ll ans = 0;
        q[nowpos] = 1;
        for(int i = 1;i<=ci[nowpos];i++){
            q[nowpos] = i;
            ans += dfs(nowpos+1);
        }
        return ans;
    }
}

int main(){
    scanf("%lld",&d);
    for(ll w = d;w;w/=10)
        ci[w%10]++;
    // for(int i = 0;i<10;i++)
    //     printf("ci:%d\n",ci[i]);
    jiecheng[1] = 1; 
    for(int i = 2;i<20;i++)
        jiecheng[i] = jiecheng[i-1] * i;
    ll ans = dfs(0);
    printf("%lld",ans);
    return 0;
}