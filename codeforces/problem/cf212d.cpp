#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1100000;

namespace BCJ{
  int f[MAXN],siz[MAXN];
  void init(int n){
    for(int i = 1;i<=n;i++)
      f[i] = i,siz[i] = 1;
  }
  int find(int x){
    return f[x] == x?x:f[x] = find(f[x]);
  }
  void merge(int x,int y){
    int fx = find(x),fy = find(y);
    if(fx == fy) return;
    f[fx] = fy;
    siz[fy] += siz[fx];
  }
  int getsize(int x){return siz[find(x)];}
}

int n,m;
int num[MAXN],s[MAXN],vis[MAXN];
int c1[MAXN],c2[MAXN],ans[MAXN];
bool cmp(int a,int b){return num[a] > num[b];}

void init(){
  scanf("%lld",&n);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&num[i]);
  }
  BCJ::init(n);
}

void addc(int x,int v,int val){
  if(x == 0) return;
  // printf("add: x:%lld val:%lld v:%lld\n",x,val,v);
  c1[1] += v*x*val;
  c2[1] -= v*1*val,c2[x+1] += v*1*val;
}

void calc(){
  for(int i = 1;i<=n;i++)
    s[i] = i;
  sort(s+1,s+n+1,cmp);
  for(int i = 1;i<=n;i++){
    int t = s[i];
    vis[t] = 1;
    int L = 0,R = 0;
    if(vis[t-1]) L = BCJ::getsize(t-1),BCJ::merge(t,t-1);
    if(vis[t+1]) R = BCJ::getsize(t+1),BCJ::merge(t,t+1);
    addc(L+R+1,1,num[t]),addc(L,-1,num[t]),addc(R,-1,num[t]);
  }
}


void solve(){
  for(int i = 1;i<=n;i++) c2[i] = c2[i-1] + c2[i];
  for(int i = 1;i<=n;i++) c2[i] = c2[i-1] + c2[i];
  for(int i = 1;i<=n;i++) c1[i] = c1[i-1] + c1[i];
  ans[1] = c1[1];
  for(int i = 1;i<=n;i++) ans[i+1] = c1[i] + c2[i];
  scanf("%lld",&m);
  for(int i = 1;i<=m;i++){
    int t;
    scanf("%lld",&t);
    printf("%.10lf\n",double(ans[t])/(n-t+1));
  }
}

signed main(){
  init();
  calc();
  solve();
  return 0;
}