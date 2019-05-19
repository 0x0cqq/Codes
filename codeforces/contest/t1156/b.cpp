#include <bits/stdc++.h>
using namespace std;


const int MAXN = 210;

int n,N = 26;
char s[MAXN],ans[MAXN];
int cnt[MAXN];

void solve(){
  scanf("%s",s+1);n = strlen(s+1);
  for(int i = 1;i<=N;i++) cnt[i] = 0;
  for(int i = 1;i<=n;i++) cnt[int(s[i]-'a'+1)]++;
  int t = 0,T = 0;
  for(int i = N;i>=1;i-=2) for(int j = 0;j<cnt[i];j++) ans[++t] = i + 'a' - 1;
  T = t;
  for(int i = N-1;i>=1;i-=2) for(int j = 0;j<cnt[i];j++) ans[++t] = i + 'a' - 1;
  ans[++t] = 0;
  // printf("%s\n",ans+1);
  if(T != n && abs(ans[T] - ans[T+1]) == 1){
    t = 0;
    for(int i = 2;i<=N;i+=2) for(int j = 0;j<cnt[i];j++) ans[++t] = i + 'a' - 1;
    T = t;
    for(int i = 1;i<=N;i+=2) for(int j = 0;j<cnt[i];j++) ans[++t] = i + 'a' - 1;
    if(T != n && abs(ans[T] - ans[T+1]) == 1){    
      printf("No answer\n");
      return;
    }
  }
  printf("%s\n",ans+1);
}

int main(){
  int T;scanf("%d",&T);
  for(int i = 1;i <= T;i++){
    solve();
  }
}