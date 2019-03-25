#include <bits/stdc++.h>
#include <bits/extc++.h>
#include <unistd.h>
#define E0 edge[e]
#define E1 edge[e^1]
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 410,MAXM = 15010;

struct Edge{
  int from,to,cap,flow,cost,nex;
}edge[MAXM*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b,int c,int d){
  edge[ecnt] = (Edge){a,b,c,0, d,fir[a]},fir[a] = ecnt++;
  edge[ecnt] = (Edge){b,a,0,0,-d,fir[b]},fir[b] = ecnt++;
}
struct Node{
  int x,d;
  bool operator < (const Node &_n)const{return d > _n.d;}
  Node(int _x,int _d):x(_x),d(_d){}
};
// #define Node pair<int,int>
// typedef __gnu_pbds::priority_queue<Node, less<Node>, __gnu_pbds::pairing_heap_tag> heap;
// typedef priority_queue< Node ,vector< Node >,greater<Node>> heap;
typedef priority_queue<Node> heap;


int n,m;
int dis[MAXN],inq[MAXN],vis[MAXN],ansf,ansc,delta;

void reduce(int s,int t){
  for(int e = 2;e <= ecnt;e++) E0.cost += dis[E0.to] - dis[E0.from];
  delta += dis[s];
}

bool bellman(int s,int t){// t 为起点
  static queue<int> q;
  memset(dis,0x3f,sizeof(int)*(n+1));while(!q.empty()) q.pop();
  dis[t] = 0,q.push(t);inq[t] = 1;
  while(!q.empty()){
    int x = q.front();q.pop();inq[x] = 0;
    for(int e = fir[x];e;e = edge[e].nex){
      int v = E0.to,c = E1.cap,f = E1.flow,l = E1.cost;
      if(c > f && dis[v] > dis[x] + l){
        dis[v] = dis[x] + l;
        if(!inq[v]) inq[v] = 1,q.push(v);
      }
    }
  }
  return dis[s] < inf;
}

bool dijkstra(int s,int t){
  memset(dis,0x3f,sizeof(int)*(n+1));
  static heap q;
  dis[t] = 0;q.push(Node(t,0));
  while(!q.empty()){
    Node p = q.top();q.pop();int x = p.x;
    if(p.d != dis[x]) continue;
    for(int e = fir[x];e;e = edge[e].nex){
      int v = E0.to,c = E1.cap,f = E1.flow,l = E1.cost;
      if(c > f && dis[v] > dis[x] + l){
        dis[v] = dis[x] + l,q.push(Node(v,dis[v]));
      }
    }
  }
  return dis[s] < inf;
}

int dfs(int x,int t,int limit = inf){
  if(x == t || limit == 0) return limit;
  vis[x] = 1; // differ from dinic
  int sumf = 0;
  for(int &e = cur[x];e;e = edge[e].nex){
    int v = E0.to,c = E0.cap,f = E0.flow,l = E0.cost;
    if(!vis[v] && c > f && l == 0){
      int newf = dfs(v,t,min(limit,c-f));
      sumf += newf,limit -= newf;
      E0.flow += newf,E1.flow -= newf;
      if(limit == 0) break;
    }
  }
  return sumf;
}

void augment(int s,int t){
  int curf = 0;
  while(memset(vis,0,sizeof(int)*(n+1)),(curf = dfs(s,t))){
    ansf += curf,ansc += curf * delta;
  }
}

void primaldual(int s,int t){
  if(!dijkstra(s,t)) return;
  ansf = ansc = delta = 0;
  do{
    reduce(s,t),augment(s,t);
  }while(dijkstra(s,t));
}

int main(){
  scanf("%d %d",&n,&m);
  int S = 1,T = n;
  for(int i = 1;i<=m;i++){
    int a,b,c,d;
    scanf("%d %d %d %d",&a,&b,&c,&d);
    addedge(a,b,c,d);
  }
  primaldual(S,T);
  printf("%d %d\n",ansf,ansc);
  return 0;
}