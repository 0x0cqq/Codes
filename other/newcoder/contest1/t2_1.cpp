#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),i##_end_=(b);i<=i##_end_;i++)
#define DOR(i,a,b) for(int i=(a),i##_end_=(b);i>=i##_end_;i--)
#define ll long long
#define M 35
using namespace std;
 
ll L,R,L1,R1;
 
 
struct P20{
 
    void solve(){
        int ans=0;
        FOR(i,L,R){
            int a=i;
            int res=1;
            while(a){
                res=res*(a%10);
                a/=10;
            }
            if(res>=L1&&res<=R1)ans++;
        }
        printf("%d\n",ans);
    }
 
}p20;
 
 
struct P100{
     
    int Num[20];
    int top;
     
    map<ll,ll>dp[21];
     
    ll dfs(int pos,int limit,ll sum){
        if(pos==0){
            if(sum==-1)sum=0;
            return L1<=sum&&sum<=R1;
        }
        if(!limit&&dp[pos][sum])return dp[pos][sum]-1;
        ll res=0;
        int Up=0;
        if(limit)Up=Num[pos];
        else Up=9;
        FOR(i,0,Up){
            if(sum==-1){
                if(i==0)res+=dfs(pos-1,limit&&i==Num[pos],-1);
                else res+=dfs(pos-1,limit&&i==Num[pos],i);
            }
            else res+=dfs(pos-1,limit&&i==Num[pos],sum*i);
        }
        if(!limit)dp[pos][sum]=res+1;
        return res;
    }
     
    ll calc(ll x){
        if(x==-1)return 0;
        top=0;
        ll a=x;
        while(a){
            Num[++top]=a%10;
            a/=10;
        }
        return dfs(top,1,-1);
    }
     
     
    void solve(){
        printf("%lld\n",calc(R)-calc(L-1));
    }
     
}p100;
 
int main(){
    scanf("%lld%lld%lld%lld",&L,&R,&L1,&R1);
//  if(L<=10000000&&R<=10000000)p20.solve();
    p100.solve();
 
    return 0;
}