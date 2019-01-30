#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;

const int MAXN = 510,MAXM = 100000;

struct Edge{
  int from,to;
  int cap,flow;
  int cost,nex;
}edge[MAXM*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b,int c,int d){
  // printf("add:%d %d %d %d\n",a,b,c,d);
  edge[ecnt] = (Edge){a,b,c,0,d,fir[a]};
  fir[a] = ecnt++;
  edge[ecnt] = (Edge){b,a,0,0,-d,fir[b]};
  fir[b] = ecnt++;
}

int dis[MAXN],vis[MAXN],minf[MAXN],pree[MAXN];
queue<int> q;

bool spfa(int s,int t){
  while(!q.empty()) q.pop();
  memset(dis,0x3f,sizeof(dis));
  memset(vis,0,sizeof(vis));
  q.push(s);dis[s] = 0,minf[s] = inf;
  while(!q.empty()){
    int nown = q.front();q.pop();
    vis[nown] = 0;
    for(int nowe = fir[nown];nowe;nowe =  edge[nowe].nex){
      Edge & e = edge[nowe];
      if(dis[e.to] > dis[nown] + e.cost && e.cap > e.flow){
        dis[e.to] = dis[nown] + e.cost;
        minf[e.to] = min(minf[nown],e.cap - e.flow);
        pree[e.to] = nowe;
        if(vis[e.to] == 0){
          q.push(e.to);
          vis[e.to] = 1;
        }
      }
    }
  }
  return dis[t] < inf;
}

int min_cost_flow(int s,int t,int k = inf){
  int ans = 0;
  while(spfa(s,t) && k > 0){
    if(dis[t] > 0) break;
    for(int nown = t,nowe = 0;nown != s;nown = edge[nowe].from){
      nowe = pree[nown];
      edge[nowe].flow += minf[t],edge[nowe^1].flow -= minf[t];
    }
    ans += dis[t] * minf[t];
  }
  return ans;
}
int n,m,k;
char s[MAXN];
char t[MAXN];

bool check(int pos,int len){
  if(pos + len - 1 > n) return 0;
  for(int i = 1;i<=len;i++) if(s[pos + i - 1] != t[i]){
    return 0;
  }
  return 1;
}

int main(){
  scanf("%d",&n),scanf("%s",s+1);
  int S = 0,T = n+2;
  scanf("%d",&m);
  for(int i = 1;i<=m;i++){
    int p;
    scanf("%s %d",t+1,&p);
    int len = strlen(t+1);
    for(int i = 1;i<=n;i++){
      if(check(i,len))
        addedge(i,i+len,1,-p);
    }
  }
  scanf("%d",&k);
  for(int i = 1;i<=n;i++){
    addedge(i,i+1,inf,0);
  }
  addedge(S,1,k,0);
  addedge(n+1,T,k,0);
  printf("%d\n",-min_cost_flow(S,T));
  return 0;
}