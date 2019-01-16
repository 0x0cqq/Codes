#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n,m;
int a[MAXN];
int num[MAXN];

set<int> S[MAXN];
int minn = 0;

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=m;i++){
    scanf("%d",&a[i]);
  }
}

void solve(){
  for(int i = 1;i<=n;i++){
    S[0].insert(i);
  }
  int now = 0;
  for(int i = 1;i<=m;i++){
    S[num[a[i]]].erase(a[i]);
    S[num[a[i]]+1].insert(a[i]);
    if(S[num[a[i]]].empty() && minn == num[a[i]]){
      while(S[minn].empty()) minn++;
    }
    num[a[i]]++;
    if(minn>now){
      putchar('1');
      now++;
    }
    else{
      putchar('0');
    }
  }
  putchar('\n');
}


int main(){
  init();
  solve();
  return 0;
}