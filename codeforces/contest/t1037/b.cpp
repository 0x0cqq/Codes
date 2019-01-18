#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 210000;

int n,s;
int c[MAXN];
ll sum[MAXN];

vector<int> a,b,d;

int main(){
  scanf("%d %d",&n,&s);
  for(int i = 1;i<=n;i++){
    scanf("%d",&c[i]);
  }
  sort(c+1,c+n+1);
  ll ans = 0;
  for(int i = 1;i<=n/2;i++){
    if(c[i] > s){
      ans += abs(c[i]-s);
    }
  }
  ans += abs(c[(n+1)/2]-s);
  for(int i = n/2+2;i<=n;i++){
    if(c[i] < s){
      ans += abs(c[i]-s);
    }
  }  
  printf("%lld\n",ans);
  return 0;
}