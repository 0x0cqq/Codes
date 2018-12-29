#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5100;

int n,m;
struct Edge{
  int a,b,l,r; 
}edge[MAXN];

set<int> S;

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=m;i++){
    scanf("%d %d %d %d",&edge[i].a,&edge[i].b,&edge[i].l,&edge[i].r);
    S.insert(edge[i].l),S.insert(edge[i].r+1);
  }
  S.insert(-1e9),S.insert(1e9);
}

vector<int> v;


namespace BCJ{
  int f[MAXN];
  void init(int n){
    for(int i = 1;i<=n;i++) f[i] = i;
  }
  int find(int x){
    return f[x] == x?x:f[x] = find(f[x]);
  }
  void merge(int x,int y){
    int fx = find(x),fy = find(y);
    if(fx == fy) return;
    f[fx] = fy;
  }
}

bool check(int x){
  BCJ::init(n);
  for(int i = 1;i<=m;i++){
    if(edge[i].l <= x && x <= edge[i].r)
      BCJ::merge(edge[i].a,edge[i].b);
  }
  return BCJ::find(1) == BCJ::find(n);
}

void solve(){
  for(auto i:S) v.push_back(i);
  int ans = 0;
  for(unsigned i = 0;i<v.size()-1;i++){
    printf("i:%d v[i]:%d\n",i,v[i]);
    if(check(v[i])){
      printf("!\n");
      ans += v[i+1] - v[i];
    }
  }
  if(ans)
    printf("%d\n",ans);
  else
    printf("Nice work, Dima!\n");
}

int main(){
  init();
  solve();
  return 0;
}