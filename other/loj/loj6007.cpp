#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 10000,MAXM = 50000;

struct Edge{
  int from,to;
  int cap,flow;
  int nex;
}edge[MAXM];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b,int c){
  edge[ecnt] = (Edge){a,b,c,0,fir[a]},fir[a] = ecnt++;
  edge[ecnt] = (Edge){b,a,0,0,fir[b]},fir[b] = ecnt++;
}

int dis[MAXN];
bool bfs(int s,int t){
  static queue<int> q;
  memset(dis,0,sizeof(dis));while(!q.empty()) q.pop();
  dis[s] = 1;q.push(s);
  while(!q.empty()){
    int x = q.front();q.pop();
    for(int e = fir[x];e;e = edge[e].nex){
      int v = edge[e].to;
      if(!dis[v] && edge[e].cap > edge[e].flow){
        dis[v] = dis[x] + 1,q.push(v);
      }
    }
  }
  return dis[t];
}

int dfs(int x,int t,int limit = inf){
  if(limit == 0 || x == t) return limit;
  int sumf = 0;
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to;
    if(dis[v] == dis[x] + 1){
      int f = dfs(v,t,min(limit,edge[e].cap - edge[e].flow));
      if(f){
        sumf += f,limit -= f,edge[e].flow += f,edge[e^1].flow -= f;
        if(limit == 0) break;
      }
    }
  }
  return sumf;
}

int dinic(int s,int t){
  int ans = 0;
  while(bfs(s,t)) ans += dfs(s,t);
  return ans;
}

int m,n,val[110][110],sum;

int _hash(int x,int y){return (x-1)*n+y;}
bool judge(int x,int y){return (x+y)&1;}


int main(){
  scanf("%d %d",&m,&n);
  for(int i = 1;i<=m;i++) for(int j = 1;j<=n;j++)
    scanf("%d",&val[i][j]),sum += val[i][j];
  int S = n*m+1,T = S + 1;
  for(int i = 1;i<=m;i++){
    for(int j = 1;j<=n;j++){
      if(judge(i,j)) addedge(S,_hash(i,j),val[i][j]);
      else           addedge(_hash(i,j),T,val[i][j]);
      if(!judge(i,j)){
        if(i > 1) addedge(_hash(i-1,j),_hash(i,j),inf);
        if(i < m) addedge(_hash(i+1,j),_hash(i,j),inf);
        if(j > 1) addedge(_hash(i,j-1),_hash(i,j),inf);
        if(j < n) addedge(_hash(i,j+1),_hash(i,j),inf);
      }
    }
  }
  printf("%d\n",sum-dinic(S,T));
  return 0;
}