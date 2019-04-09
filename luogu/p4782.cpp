#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2100000;

struct Edge{
  int to,nex;
}edge[MAXN];int ecnt = 2;
int fir[MAXN];
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]},fir[a] = ecnt++;
}

int n,m;

int p(int x,int op){return x + (op == 0?n:0);}

void add_or(int i,int a,int j,int b){
  addedge(p(i,a^1),p(j,b)),addedge(p(j,b^1),p(i,a));
}

int dfn[MAXN],low[MAXN],col[MAXN],cnum,S[MAXN];

void tarjan(int x){
  dfn[x] = low[x] = ++dfn[0];S[++S[0]] = x;
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to;
    if(!dfn[v]) tarjan(v),low[x] = min(low[x],low[v]);
    else if(!col[v]) low[x] = min(low[x],dfn[v]);
  }
  if(low[x] == dfn[x]){
    for(++cnum;S[S[0]] != x;--S[0]) col[S[S[0]]] = cnum;
    col[S[S[0]--]] = cnum;
  }
}

void solve_sat(){
  for(int i = 1;i<=n*2;i++) if(!dfn[i]) tarjan(i);
  for(int i = 1;i<=n;i++){
    // printf("%d: %d %d\n",i,col[p(i,0)],col[p(i,1)]);
    if(col[p(i,0)] == 0 || col[p(i,1)] == 0) assert(0);
    if(col[p(i,0)] == col[p(i,1)])  return (void)(printf("IMPOSSIBLE\n"));
  }
  
  printf("POSSIBLE\n");
  for(int i = 1;i<=n;i++) printf(col[p(i,0)] > col[p(i,1)] ? "1 " : "0 ");
  printf("\n");
}

void init(){
  scanf("%d %d",&n,&m);
  for(int x = 1;x <= m;x++){
    int i,j,a,b;
    scanf("%d %d %d %d",&i,&a,&j,&b);
    add_or(i,a,j,b);
  }
}


int main(){
  init();
  solve_sat();
  return 0;
}