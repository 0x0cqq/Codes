#include <bits/stdc++.h>
using namespace std;


const int MAXN = 210000;
int n;
int a[MAXN],b[MAXN],ans[MAXN];
multiset<int> S;
inline void pmod(int &x){x = (x >= n ? x - n : x);}

int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++) scanf("%d",&a[i]);
  for(int i = 1;i<=n;i++) scanf("%d",&b[i]),S.insert(b[i]);
  for(int i = 1;i<=n;i++){
    auto it = S.lower_bound(n-a[i]);
    if(it != S.end()){
      ans[i] = a[i] + (*it);
      S.erase(it);
    }
    else{
      ans[i] = a[i] + *(S.begin());
      S.erase(S.begin());
    }
  }
  for(int i = 1;i<=n;i++) pmod(ans[i]),printf("%d ",ans[i]);
  printf("\n");
  return 0;
}