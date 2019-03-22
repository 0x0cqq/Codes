#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 1100,MAXM = 1100*25*2;

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
  dis[s] = 1,q.push(s);
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
        sumf += f,limit -= f;
        edge[e].flow += f,edge[e^1].flow -= f;
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

int k,n,m;

int main(){
  scanf("%d %d",&k,&n);
  int S = k + n + 1,T = S + 1;
  for(int i = 1;i<=k;i++){
    int tmp;scanf("%d",&tmp);    
    addedge(S,i,tmp),m += tmp;
  }
  for(int i = 1;i<=n;i++){
    int p,tmp;
    scanf("%d",&p);
    addedge(i+k,T,1);
    for(int x = 1;x <= p;x++){
      scanf("%d",&tmp);
      addedge(tmp,i+k,1);
    }
  }
  int ans = dinic(S,T);
  if(ans != m) printf("No Solution!\n");
  else{
    for(int i = 1;i<=k;i++){
      printf("%d: ",i);
      for(int e = fir[i];e;e = edge[e].nex){int v = edge[e].to;
        if(k+1<=v && v<=k+n && edge[e].flow == 1) printf("%d ",v-k);
      }
      printf("\n");
    }
  }
  return 0;
}