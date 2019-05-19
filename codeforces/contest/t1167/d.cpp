#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n;
char s[MAXN];
int ans[MAXN];

int cnt1,cnt2;

int main(){
  scanf("%d",&n);
  scanf("%s",s+1);
  for(int i = 1;i<=n;i++){
    if(s[i] == '('){
      if(cnt1 <= cnt2) ans[i] = 0,cnt1++;
      else ans[i] = 1,cnt2++;
    }
    else{
      if(cnt1 <= cnt2) ans[i] = 1,cnt2--;
      else ans[i] = 0,cnt1--;
    }
  }
  for(int i = 1;i<=n;i++){
    printf("%d",ans[i]);
  }
  printf("\n");
}