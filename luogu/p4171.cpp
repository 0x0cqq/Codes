#include <bits/stdc++.h>
using namespace std;

const int MAXN = 11100;

struct Edge{
  int to,nex;
}edge[MAXN*2];int ecnt = 2;
int fir[MAXN];
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]},fir[a] = ecnt++;
}
void clear(){ecnt = 2;memset(fir,0,sizeof(fir));}

int n,m;

int p(int x,int op){return x + op * n;}
void add(int i,int a,int j,int b){
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

bool solve_sat(){
  memset(dfn,0,sizeof(dfn)),memset(low,0,sizeof(low));
  memset(S,0,sizeof(S)),memset(col,0,sizeof(col));
  cnum = 0;
  for(int i = 1;i <= 2*n;i++) if(!dfn[i]) tarjan(i);
  for(int i = 1;i<=n;i++) if(col[p(i,0)] == col[p(i,1)]) return 0;
  return 1;
}

void init(){
  scanf("%d %d",&n,&m);
  char s1[10],s2[10];int x,y;
  for(int i = 1;i<=m;i++){
    scanf("%s %s",s1,s2);
    sscanf(s1+1,"%d",&x),sscanf(s2+1,"%d",&y);
    add(x,s1[0]=='h',y,s2[0]=='h');
  }
}

int main(){
  int T;scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    clear(),init();
    printf(solve_sat()?"GOOD\n":"BAD\n");
  }
  return 0;
}