#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 5100;

int n;
int c[MAXN],f[MAXN];
int lst[MAXN];

int cnt[MAXN];
stack<int> S;

signed main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&c[i]);
  }
  int ans = 0;
  for(int i = 1;i<=n;i++){
    f[i] = lst[c[i]];
    lst[c[i]] = i;
  }
  for(int i = 1;i<=n;i++){
    if(cnt[c[i]] == 0){
      S.push(c[i]);
      cnt[c[i]]++;
    }
    else{
      while(S.top() != c[i]){
        ans++,cnt[S.top()]--;
        S.pop();
      }
      
    }
  }
  ans += S.size() - 1;
  printf("%d\n",ans);
  return 0;
}