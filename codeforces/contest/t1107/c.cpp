#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n,k;
int p[MAXN];
char s[MAXN];

multiset<int> S;

int main(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=n;i++){
    scanf("%d",&p[i]);
  }
  scanf("%s",s+1);
  long long ans = 0; 
  for(int i = 1;i<=n+1;i++){
    if(s[i] != s[i-1]){
      if(int(S.size()) > k){
        while(int(S.size()) > k){
          ans -= *S.begin();
          S.erase(S.begin());
        }
      }
      S.clear();
    }

    S.insert(p[i]);
    ans += p[i];
  }
  printf("%lld\n",ans);
  return 0;
}