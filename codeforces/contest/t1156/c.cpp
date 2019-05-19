#include <bits/stdc++.h>
using namespace std;


const int MAXN = 210000;

int n,z;
int a[MAXN];

bool check(int k){
  for(int i = 1;i<=k;i++){
    if(a[n-k+i] - a[i] < z){
      return 0;
    }
  }
  return 1;
}

void init(){
  scanf("%d %d",&n,&z);
  for(int i = 1;i<=n;i++) scanf("%d",&a[i]);
  sort(a+1,a+n+1);
}

void solve(){
  int L = 0,R = n/2;
  while(L!=R){
    int mid = (L+R+1)/2;
    if(check(mid)){
      L = mid;
    }
    else{
      R = mid-1;
    }
  }
  printf("%d\n",L);
}

int main(){
  init();
  solve();
  return 0;
}