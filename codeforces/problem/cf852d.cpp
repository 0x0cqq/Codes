#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1210,MAXM = MAXN*MAXN/2;

struct Edge{
  int from,to;
  int cap,flow;
  int nex;
}edge[MAXM*2];
int fir[MAXN],cur[MAXN],ecnt = 2;
void addedge(int a,int b,int c){
  // printf("addedge:%d %d\n",a,b);
  edge[ecnt] = (Edge){a,b,c,0,fir[a]};
  fir[a] = ecnt++;
  edge[ecnt] = (Edge){b,a,0,0,fir[b]};
  fir[b] = ecnt++;
}

int dis[MAXN];
queue<int> q;

bool bfs(int s,int t){
  while(!q.empty()) q.pop();
  memset(dis,0,sizeof(dis));
  memcpy(cur,fir,sizeof(fir));
  dis[s] = 1;q.push(s);
  while(!q.empty()){
    int nown = q.front();q.pop();
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
      Edge &e = edge[nowe];
      if(dis[e.to] == 0 && e.cap > e.flow){
        dis[e.to] = dis[nown] + 1;
        q.push(e.to);
        if(e.to == t) return 1;
      }
    }
  }
  return 0;
}

int dfs(int nown,int t,int limit = 1e9){
  if(nown == t || limit == 0) return limit;
  int sumf = 0;
  for(int &nowe = cur[nown];nowe;nowe = edge[nowe].nex){
    Edge &e = edge[nowe];
    if(dis[e.to] == dis[nown] + 1 && e.cap > e.flow){
      int f = dfs(e.to,t,min(limit,e.cap - e.flow));
      if(f){
        edge[nowe].flow += f;
        edge[nowe^1].flow -= f;
        limit -= f,sumf += f;
        if(limit == 0) break;
      }
    }
  }
  return sumf;
}

int dinic(int s,int t){
  int ans = 0;
  while(bfs(s,t)){
    ans += dfs(s,t);
  }
  return ans;
}

int v,e,n,k;
int st[MAXN];
int DIS[MAXN][MAXN];


void floyd(int n){
  for(int i = 1;i<=n;i++) DIS[i][i] = 0;
  for(int k = 1;k<=n;k++){
    for(int i = 1;i<=n;i++){
      for(int j = 1;j<=n;j++){
        DIS[i][j] = min(DIS[i][j],DIS[i][k] + DIS[k][j]);
      }
    }
  }
}

void init(){
  scanf("%d %d %d %d",&v,&e,&n,&k);
  for(int i = 1;i<=n;i++) scanf("%d",&st[i]);
  memset(DIS,0x3f,sizeof(DIS));
  for(int i = 1;i<=e;i++){
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    DIS[a][b] = DIS[b][a] = min(DIS[a][b],c);
  }
  floyd(v);
}

int check(int val){
  int S = 2*v+1,T = 2*v+2;
  memset(fir,0,sizeof(fir));
  ecnt = 2;
  for(int i = 1;i<=n;i++){
    int x = st[i];
    addedge(S,x,1);
    for(int y = 1;y<=v;y++)if(DIS[x][y] <= val){
      addedge(x,y+v,1);
    }
  }
  for(int x = 1;x <= v;x++){
    addedge(x+v,T,1);
  }
  return dinic(S,T);
}

void solve(){
  int L = 0,R = 1731312;
  while(L != R){
    int mid = (L+R)/2;
    int tmp = check(mid);// 在mid时间内能不能达成目标
    // printf("%d:%d\n",mid,tmp);
    if(tmp >= k){
      R = mid;
    }
    else{
      L = mid+1;
    }
  }
  printf("%d\n",L == 1731312 ? -1 : L);
}



int main(){
  init();
  solve();
  return 0;
}