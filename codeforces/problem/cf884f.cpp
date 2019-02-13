#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110,inf = 0x3f3f3f3f;

struct Edge{
  int from,to;
  int cap,flow;
  int cost,nex;
}edge[1000000];
int fir[MAXN*26],ecnt = 2;
void addedge(int a,int b,int c,int d){
  edge[ecnt] = (Edge){a,b,c,0,d,fir[a]};
  fir[a] = ecnt++;
  edge[ecnt] = (Edge){b,a,0,0,-d,fir[b]};
  fir[b] = ecnt++;
}

int dis[MAXN*26],vis[MAXN*26],minf[MAXN*26],pe[MAXN*26];
queue<int> q;

bool spfa(int s,int t){
  memset(dis,0x3f,sizeof(dis));
  while(!q.empty()) q.pop();
  dis[s] = 0,minf[s] = inf;q.push(s);
  while(!q.empty()){
    int nown = q.front();q.pop();
    vis[nown] = 0;
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
      Edge &e = edge[nowe];
      if(dis[e.to] > dis[nown] + e.cost && e.cap > e.flow){
        dis[e.to] = dis[nown] + e.cost;
        pe[e.to] = nowe,minf[e.to] = min(minf[nown],e.cap - e.flow);
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
    for(int nown = t,nowe;nown != s;nown = edge[nowe].from){
      nowe = pe[nown];
      edge[nowe].flow += minf[t];
      edge[nowe^1].flow -= minf[t];
    }
    ans += minf[t] * dis[t];
  }
  return ans;
}

int n;
char s[MAXN];
int p[MAXN],c[MAXN];

void init(){
  scanf("%d",&n),scanf("%s",s+1);
  for(int i = 1;i<=n;i++) scanf("%d",&p[i]);
  for(int i = 1;i<=n;i++) c[s[i]-'a']++;
}

void solve(){
  // 位置节点为 1->n ，剩余节点现加cnt
  int cnt = n;
  int S = ++cnt,T = ++cnt;
  for(int x = 0;x<26;x++){
    int Cnode = ++cnt;
    addedge(S,Cnode,c[x],0);
    for(int i = 1;i <= n/2;i++){
      int tmp = ++cnt;
      addedge(Cnode,tmp,1,0);
      addedge(tmp,    i,1,x == s[i]     - 'a'?-p[i]:0);
      addedge(tmp,n-i+1,1,x == s[n-i+1] - 'a'?-p[n-i+1]:0);
    }
  }
  for(int i = 1;i <= n;i++) addedge(i,T,1,0);
  printf("%d\n",-min_cost_flow(S,T));
}

int main(){
  init();
  solve();
  return 0;
}