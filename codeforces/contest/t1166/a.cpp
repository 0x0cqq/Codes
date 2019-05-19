#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30;

int n;
int cnt[MAXN];
char s[MAXN];

int calc(int x){
  return x * (x-1) / 2;
}

int main(){
  scanf("%d",&n);
  for(int i = 1;i <= n;i++){
    scanf("%s",s);
    cnt[s[0]-'a'+1]++;
  }
  int ans = 0;
  for(int i = 1;i<=26;i++){
    ans += calc(cnt[i]/2) + calc((cnt[i]+1)/2);
  }
  printf("%d\n",ans);
  return 0;
}