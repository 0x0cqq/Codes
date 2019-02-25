#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 210000;

int n,m,k;
char s[MAXN];
int cnt[MAXN];

void init(){
  scanf("%d %d %d",&n,&m,&k);
  scanf("%s",s);
  for(int i = 0;i<26;i++) cnt[i] = 0;
  for(int i = 0;i<k;i++) cnt[s[i]-'A']++;
}

int dp[MAXN];


void get_beibao(int x){
  for(int i = 0;i<k;i++) dp[i] = 0;
  dp[0] = 1;
  int sum = 0;
  for(int i = 0;i<26;i++)if(i != x){
    for(int j = sum;j>=0;--j)if(dp[j]){
      dp[j+cnt[i]] = 1;
    }
    sum += cnt[i];
  }
}

void solve(){
  ll ans = 1e18;
  for(int ch = 0;ch<26;ch++){
    if(cnt[ch] == 0) continue;
    get_beibao(ch);
    for(int j = 0;j<=min(cnt[ch],n);j++){
      int t = k - (n-j) - cnt[ch];// 不会产生任何交叉的部分
      if(dp[n-j]){
        // printf("    %d:%d,ans:%lld\n",j,t,1LL * j * (max(0,m-t)));
        ans = min(ans,1LL * j * (max(0,m-t)));
      }
    }
  }
  printf("%lld\n",ans);
}

int main(){
  int T;
  scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    init();
    solve();
  }
  return 0;
}