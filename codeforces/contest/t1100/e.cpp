#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

struct Node{
  int u,v,c,id;
}e[MAXN];
bool cmp(const Node &a,const Node &b){return a.c < b.c;}

int n,m;

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=m;i++){
    scanf("%d %d %d",&e[i].u,&e[i].v,&e[i].c);
    e[i].id = i;
  }
  sort(e+1,e+m+1,cmp);
}
int d[MAXN];
int idd[MAXN];
vector<int> edge[MAXN];
queue<int> q;

bool check(int x){ // 可以达成
  // printf("check:%d\n",x);
  memset(d,0,sizeof(d));
  for(int i = 1;i<=n;i++){
    edge[i].clear();
  }
  for(int i = m;i>=1;i--){
    if(e[i].c <= x) break;
    edge[e[i].u].push_back(e[i].v); 
    // printf("%d %d\n",e[i].u,e[i].v);
    d[e[i].v]++;
  }
  while(!q.empty()) q.pop();
  for(int i = 1;i<=n;i++){
    if(d[i] == 0) q.push(i);
  }
  for(int i = 1;i<=n;i++){
    if(q.empty()) return 0;
    int nown = q.front();q.pop();
    idd[nown] = i;
    for(auto j : edge[nown]){
      d[j]--;
      if(d[j] == 0) q.push(j);
    }
  }
  // for(int i = 1;i<=n;i++){
  //   printf("%d ",idd[i]);
  // }
  // printf("\n");
  return 1;
}

void output(int x){
  vector<int> ans;
  for(int i = 1;i<=m;i++){
    if(e[i].c > x) break;
    if(idd[e[i].u] > idd[e[i].v]){
      ans.push_back(e[i].id);
    }
  }
  printf("%d\n",int(ans.size()));
  for(auto i: ans){
    printf("%d ",i);
  }
  printf("\n");
}


void solve(){
  int L = 0,R = 1e9+10;
  while(L != R){
    int mid = (L+R)/2;
    int t = check(mid);
    // printf("%d\n",(t));
    if(t){
      R = mid;
    }
    else{
      L = mid+1;
    }
  }
  printf("%d ",L);
  check(L);
  output(L);
}

int main(){
  init();
  solve();
  return 0;
}