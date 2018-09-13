#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

const int MAXN = 110000,MAXQ = 4000;

int n,m,Q;
int num[MAXN];
int back[MAXN];
int ans1[MAXN],ans2[MAXN];

map<int,int> S;

struct Query{
  int id,l,r,a,b;
}q[MAXN];

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    scanf("%d",&num[i]);
  }
  for(int i = 1;i<=m;i++){
    scanf("%d %d %d %d",&q[i].l,&q[i].r,&q[i].a,&q[i].b);
  }
}

void solve(){
  static int times[MAXN];
  static bool vis[MAXN];
  for(int i = 1;i<=m;i++){
    memset(times,0,sizeof(times));
    memset(vis,0,sizeof(vis));
    for(int j = q[i].l;j<=q[i].r;j++){
      vis[num[j]] = 1;
      times[num[j]]++;
    }
    int ans = 0;
    for(int j = q[i].a;j<=q[i].b;j++){
      ans += times[j];
    }
    printf("%d ",ans);
    ans = 0;
    for(int j = q[i].a;j<=q[i].b;j++){
      ans += int(vis[j]);
    }
    printf("%d\n",ans);
  }
}

int main(){
  init();
  solve();
  return 0;
}