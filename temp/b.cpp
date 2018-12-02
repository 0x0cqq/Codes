#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 512;
const int mod = 7;

int n,a[MAXN],d[MAXN];
int cnt[MAXN];

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
    d[i] = ((a[i] - a[i-1])+mod)%mod;
    cnt[d[i]]++;
  }
  cnt[7-a[n]]++;
}


int v[3];
int dp[MAXN][MAXN][8];
int solve_1(){
  for(int i = 0;i<MAXN;i++){
    for(int j = 0;j<MAXN;j++){
      for(int w = 0;w<8;w++){
        dp[i][j][w] = -inf;
      }
    }
  }
  dp[0][0][0] = 0;
  for(int a = 0;a<=cnt[v[0]];a++){
    for(int b = 0;b<=cnt[v[1]];b++){
      for(int c = 0;c<=cnt[v[2]];c++){
        if(a == 0 && b == 0 && c == 0) continue;
        int tmp[7];
        for(int w = 0;w<=6;w++){
          int ans = -inf;
          if(a > 0)
            ans = max(ans,dp[b][c][(w+v[0])%7] + ((w+v[0])==7?1:0));
          if(b > 0)
            ans = max(ans,dp[b-1][c][(w+v[1])%7] + ((w+v[1])==7?1:0));
          if(c > 0)
            ans = max(ans,dp[b][c-1][(w+v[2])%7] + ((w+v[2])==7?1:0));
          tmp[w] = ans;
        }
        for(int w = 0;w<=6;w++){
          dp[b][c][w] = tmp[w];
        }
      }
    }
  }
  return dp[cnt[v[1]]][cnt[v[2]]][0];
}

int solve(){
  int ans = 0;
  for(int i = 1;i<=6;i++){
    if(i >= 7 - i) break;
    int t = min(cnt[i],cnt[7-i]);
    ans += t;
    cnt[i] -= t,cnt[7-i] -= t;
  }
  int sum = 0;
  vector<int> V;
  for(int i = 1;i<=6;i++){
    if(cnt[i] > 0){
      V.push_back(i);
    }
    sum += cnt[i];
  }
  
  if(V.size() == 0)
    return ans;
  else if(V.size() == 1)
    return ans + 6 * cnt[V[0]]/7;
  else{
    V.push_back(7);
    v[0] = V[0],v[1] = V[1],v[2] = V[2];
    return ans + sum - solve_1();
    return 0;
  }
}

int main(){
  init();
  printf("%d\n",solve());
  return 0;
}