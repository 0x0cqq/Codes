#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1110000;

int n;

char s[MAXN];
int cnt1,cnt2;// = 0
char t[MAXN];

int main(){
  scanf("%d",&n);
  scanf("%s",s+1);
  scanf("%s",t+1);
  int ans = 0;
  int last = 0;
  for(int i = 1;i<=n;i++){
    if(i > 1 && s[i] != s[i-1] && t[i] != t[i-1] && s[i] != t[i] && i-1 > last){
      ans--;
      last = i;
    }
    if(s[i] != t[i]) ans++;
  }
  printf("%d\n",ans);
  return 0;
}