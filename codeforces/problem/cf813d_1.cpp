#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5100*2,MAXC = 100100;

struct Edge{
  int from,to;
  int cap,flow;
  int cost,nex;
}edge[MAXN*10];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b,int c,int d){
  // printf("addedge:%d %d %d %d\n",a,b,c,d);
  edge[ecnt] = (Edge){a,b,c,0,d,fir[a]};
  fir[a] = ecnt++;
  edge[ecnt] = (Edge){b,a,0,0,-d,fir[b]};
  fir[b] = ecnt++;
}

int n,a[MAXN];
int dis[MAXN],vis[MAXN],pree[MAXN];
queue<int> q;

bool spfa(int s,int t){
  memset(dis,0x3f,sizeof(dis));
  memset(vis,0,sizeof(vis));
  while(!q.empty()) q.pop();
  dis[s] = 0;q.push(s);
  while(!q.empty()){
    int nown = q.front();q.pop();
    vis[nown] = 0;
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
      Edge &e = edge[nowe];
      if(dis[e.to] > dis[nown] + e.cost && e.cap > e.flow){
        dis[e.to] = dis[nown] + e.cost;
        pree[e.to] = nowe;
        if(vis[e.to] == 0){
          vis[e.to] = 1;
          q.push(e.to);
        }
      }
    }
  }
  return dis[t] < 0x3f3f3f3f;
}

int min_cost_flow(int s,int t,int k){
  int ans = 0;
  while(spfa(s,t) && k > 0){
    // printf("!!!-----------------\n");
    int nown = t,nowe = 0,limit = k;
    while(nown != s){
      nowe = pree[nown];
      limit = min(limit,edge[nowe].cap - edge[nowe].flow);
      nown = edge[nowe].from;
    }
    nown = t;
    while(nown != s){
      nowe = pree[nown];
      // printf("%d\n",nown);
      edge[nowe].flow += limit;
      edge[nowe^1].flow -= limit;

      nown = edge[nowe].from;
    }
    ans += limit * dis[t];
    k -= limit;
  }
  return ans;
}
vector<int> num[MAXC],mod[7];

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
    num[a[i]].push_back(i);
    mod[a[i] % 7].push_back(i);
  }
}


void solve(){
  int S = 0,T = 2*n+1;
  for(int i = 1;i<=n;i++){
    addedge(S    ,2*i-1,1,0 );
    addedge(2*i-1,2*i  ,1,-1);
    addedge(2*i  ,T    ,1,0 );
  }
  for(int i = 1;i<=n;i++){
    vector<int>::iterator it;
    it = upper_bound(num[a[i]-1].begin(),num[a[i]-1].end(),i);
    if(it != num[a[i]-1].end()){
      addedge(2*i-1,2*(*it)-1,2,0);
      addedge(2*i  ,2*(*it)-1,1,0);
    }
    it = upper_bound(num[a[i]+1].begin(),num[a[i]+1].end(),i);
    if(it != num[a[i]+1].end()){
      addedge(2*i-1,2*(*it)-1,2,0);
      addedge(2*i  ,2*(*it)-1,1,0);
    }
    it = upper_bound(mod[a[i]%7].begin(),mod[a[i]%7].end(),i);
    if(it != mod[a[i]%7].end()){
      addedge(2*i-1,2*(*it)-1,2,0);
      addedge(2*i  ,2*(*it)-1,1,0);
    }
  }
  printf("%d\n",-min_cost_flow(S,T,2));
}

int main(){
  init();
  solve();
}