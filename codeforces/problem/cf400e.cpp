#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 210000,logn = 21;

int n,m,ANS = 0;
int num[MAXN];
set<int> S[logn];

int getpre(int pos,int x){// 小于 pos 的第一个 x 
  auto it = S[x].lower_bound(pos);
  return *(--it);
}
int getnex(int pos,int x){// 大于 pos 的第一个 x
  auto it = S[x].upper_bound(pos);
  return *it; 
}
int calc(int now,int last,int x){
  // printf("calc: now:%lld last:%lld x:%lld cal:%lld\n",now,last,x,(now-last) * (n-now+1) * (1<<x));
  return (now-last) * (n-now+1) * (1LL<<x);
}

void update(int p,int v){
  for(int i = 0;i<logn;i++){
    int tmp = (v&(1<<i))!=0;
    if(tmp != (int)(S[i].count(p))) continue;
    int last = getpre(p,i),nex = getnex(p,i);
    if(!tmp){
      // printf("---insert:\n");
      ANS += calc(nex,last,i);
      ANS -= calc(nex,p,i);ANS -= calc(p,last,i);  
      S[i].insert(p);
      // printf("---ANS:%lld\n",ANS);
    }
    else{
      // printf("---ERASE:\n");
      ANS -= calc(nex,last,i);
      ANS += calc(nex,p,i);ANS += calc(p,last,i); 
      // printf("---ANS:%lld\n",ANS);
      S[i].erase(p);
    }
  }
}

void init(){
  scanf("%lld %lld",&n,&m);
  for(int x = 0;x<logn;x++)
    for(int i = 1;i<=n;i++) S[x].insert(i);
  for(int i = 0;i<logn;i++) S[i].insert(0),S[i].insert(n+1);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&num[i]);
    update(i,num[i]);
  }
}

void solve(){
  int v,p;
  for(int i = 1;i<=m;i++){
    // printf("--------------------------\n");
    scanf("%lld %lld",&p,&v);
    update(p,v);
    printf("%lld\n",ANS);  
  }
}

signed main(){
  init();
  solve();
  return 0;
}