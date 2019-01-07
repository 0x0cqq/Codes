#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110000;

struct Edge{
  int to,nex;
}edge[MAXN];int ecnt = 2;
int fir[MAXN];
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}

// priority_queue<int,vector<int>,greater<int> > q;
priority_queue<int> q;

int n,m,in[MAXN];
int ans[MAXN];

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=m;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    addedge(b,a);
    in[a]++;
  }
}

void solve(){
  for(int i = 1;i<=n;i++){
    if(in[i] == 0) q.push(i);
  }
  int cnt = n;
  while(!q.empty()){
    int nown = q.top();q.pop();
    ans[nown] = cnt--;
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
      int v = edge[nowe].to;--in[v];
      if(in[v] == 0) q.push(v);
    }
  }
  for(int i = 1;i<=n;i++){
    printf("%d ",ans[i]);
  }
  printf("\n");
}

int main(){
  init();
  solve();
  return 0;
}