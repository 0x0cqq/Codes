#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 210000;

int n,m,k;
int a[MAXN];
int t[MAXN],s[MAXN];

bool cmp(int x,int y){
  return a[x] > a[y];
}

void init(){
  cin >> n >> m >> k;
  for(int i = 1;i<=n;i++)
    cin >> a[i];
}


void solve(){
  for(int i = 1;i<=n;i++)
    t[i] = i;
  sort(t+1,t+n+1,cmp);
  ll ans = 0;
  for(int i = 1;i<=m*k;i++){
    s[t[i]] = 1;
    ans += a[t[i]];
  }
  cout << ans << endl;
  static int vis[MAXN];
  vis[0] = 1;
  vis[m*k] = 1;
  for(int i = 1;i<=n-1;i++){
    s[i] += s[i-1];
    if(s[i] % m == 0 && vis[s[i]] == 0){
      cout << i << " ";
      vis[s[i]] = 1;
    }
  }
  puts("");
}

signed main(){
  init();
  solve();
  return 0;
}