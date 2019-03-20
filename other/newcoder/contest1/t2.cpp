#include <cstdio>
#include <cmath>
#include <cstring>
#define ll long long
using namespace std;
 
double l2,l3,l5,l7,limit;
 
ll L,R,L1,R1;
ll f2[10],f3[10],f5[10],f7[10];
ll m2[55],m3[40],m5[20],m7[20],m10[20];
ll dp[20][55][40][20][20];// dp[left][2][3][5][7]
 
ll cc(int a,int b,int c,int d){
  if(a*l2 + b*l3 + c*l5 + d*l7 >= limit) return 2e18;
  return m2[a] * m3[b] * m5[c] * m7[d];
}

ll calx(ll x){
  static int num[20];
  int cnt = 0;
  while(x){
    num[++cnt] = x%10;
    x /= 10;
  }
  ll ans = 1;
  for(int i = cnt;i>=1;i--) ans *= num[i];
  return ans >= L1 && ans <= R1;
}
 
void init(){
  scanf("%lld %lld %lld %lld",&L,&R,&L1,&R1);
  for(int t = 1;t<=9;t++){
    int i = t;
    while(i % 2 == 0) f2[t]++,i/=2;
    while(i % 3 == 0) f3[t]++,i/=3;
    while(i % 5 == 0) f5[t]++,i/=5;
    while(i % 7 == 0) f7[t]++,i/=7;
  }
  m2[0] = m3[0] = m5[0] = m7[0] = m10[0] = 1;
  for(int i = 1;i<=3*18;i++) m2[i] = m2[i-1] * 2;
  for(int i = 1;i<=2*18;i++) m3[i] = m3[i-1] * 3;
  for(int i = 1;i<=18;i++) m5[i] = m5[i-1] * 5;
  for(int i = 1;i<=18;i++) m7[i] = m7[i-1] * 7;
  for(int i = 1;i<=18;i++) m10[i] = m10[i-1] * 10;
  l2 = log10(2),l3 = log10(3),l5 = log10(5),l7 = log10(7);
  limit = log10(5e18);
}
 
 
void cald(){
  //printf("!!!!\n");
  for(int a = 0;a<=3*18;a++){
    for(int b = 0;b <= 2*18;b++){
      for(int c = 0;c <= 18;c++){
        for(int d = 0;d <= 18;d++){
          if(L1<= cc(a,b,c,d) && cc(a,b,c,d) <= R1){
            //printf("%d %d %d %d\n",a,b,c,d);
            dp[0][a][b][c][d] = 1;
          }
        }
      }
    }
  }
  //printf("!!!!\n");
  for(int left = 1;left<=18;left++){
    for(int a = 0;a<=3*18;a++){
      for(int b = 0;b <= 2*18;b++){
        for(int c = 0;c <= 18;c++){
          for(int d = 0;d <= 18;d++){
            //if(cc(a,b,c,d) >= R1 && L1 != 0) continue;
            ll &ans = dp[left][a][b][c][d];
            if(cc(a,b,c,d) <= R1)
              for(int i = 1;i<=9;i++)
                ans += dp[left-1][a+f2[i]][b+f3[i]][c+f5[i]][d+f7[i]];
            if(L1 == 0) ans += m10[left-1];
          }
        }
      }
    }  
  }
 
}
 
ll calc(ll x){
  ll t = x;
  if(x == -1) return 0;
  if(x == 0) return L1==0;
  static int num[20];
  int cnt = 0;
  while(x) num[++cnt] = x%10,x /= 10;
  ll ans = 0;
  int a = 0,b = 0,c = 0,d = 0;
  for(int len = cnt;len>=1;--len){
    for(int i = 1;i<num[len];i++){
      ans += dp[len-1][a+f2[i]][b+f3[i]][c+f5[i]][d+f7[i]];
    }
    if(cnt != len && L1 == 0) ans += m10[len-1];
    if(num[len] == 0 && L1 != 0) break;
    else if(num[len] == 0 && L1 == 0){
      for(int ww = len-1;ww>=1;ww--)
        ans += num[ww]*m10[ww-1];
      ans -= 1;
      break;
    }
    a+=f2[num[len]],b+=f3[num[len]],c+=f5[num[len]],d+=f7[num[len]];
  }
  ans+=calx(t);
  for(int len = cnt-1;len>=1;--len){
    for(int i = 1;i<=9;i++){
      ans += dp[len-1][f2[i]][f3[i]][f5[i]][f7[i]];
    }
  }
  //printf("%lld\n",ans);
  if(L1 == 0) ans++;
  return ans;
}
 
void solve(){
  cald();
  printf("%lld\n",calc(R)-calc(L-1));
}
 
 
int main(){
  init();
  solve();
  return 0;
}