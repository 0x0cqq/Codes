#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;

const int MAXN = 1100000;
int n,q,a[MAXN];

struct Q{
  int x,id;
};

vector<Q> qu[MAXN];
int ans[MAXN];
int vis[MAXN];

vector<int> T,tmp;

void init(){
  scanf("%d %d",&n,&q);
  for(int i = 1;i<=n;i++) scanf("%d",&a[i]);
  for(int i = 1;i<=q;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    qu[a].push_back((Q){b,i});
  }
}

void solve(){
  vis[0] = 1;
  T.push_back(0);
  int now = 1;
  for(int i = 1;i<=n;i++){
    if(vis[a[i]] == 1)
      now = now * 2 % mod;
    else{
      tmp.clear();
      for(auto x:T){
        tmp.push_back(a[i] ^ x);
        vis[a[i] ^ x] = 1;
      }
      for(auto x:tmp) T.push_back(x);
    }
    for(auto q:qu[i]) ans[q.id] = vis[q.x] ? now : 0;
  }
  for(int i = 1;i<=q;i++){
    printf("%d\n",ans[i]);
  }
}

int main(){
  init();
  solve();
  return 0;
}