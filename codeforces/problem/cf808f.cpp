#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;
const int MAXN = 120,MAXM = MAXN*MAXN*5;

struct Edge{
  int from,to;
  int cap,flow;
  int nex;
}edge[MAXM*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b,int c){
  // printf("%d %d %d\n",a,b,c);
  edge[ecnt] = (Edge){a,b,c,0,fir[a]};
  fir[a] = ecnt++;
  edge[ecnt] = (Edge){b,a,0,0,fir[b]};
  fir[b] = ecnt++;
}

int dis[MAXN];
queue<int> q;

bool bfs(int s,int t){
  memset(dis,0,sizeof(dis));
  while(!q.empty()) q.pop();
  dis[s] = 1;q.push(s);
  while(!q.empty()){
    int nown = q.front();q.pop();
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
      int v = edge[nowe].to;
      if(dis[v] == 0 && edge[nowe].cap > edge[nowe].flow){
        dis[v] = dis[nown] + 1;
        q.push(v);
      }
    }
  }
  return dis[t] != 0;
}

int dfs(int nown,int t,int limit = inf){
  if(nown == t || limit == 0) return limit;
  int sumf = 0;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(dis[v] == dis[nown] + 1 && edge[nowe].cap > edge[nowe].flow){
      int f = dfs(v,t,min(limit,edge[nowe].cap - edge[nowe].flow));
      if(f > 0){
        edge[nowe].flow += f,edge[nowe^1].flow -= f;
        sumf += f,limit -= f;
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

struct Card{
  int p,c,l;
}C[MAXN];

int n,k,pri[210000];

bool check(int x){// 所有小于等于 x 的能不能完成目标
  ecnt = 2;memset(fir,0,sizeof(fir));
  vector<Card> t;//1视作奇数
  int tmp = -inf;
  for(int i = 1;i<=n;i++){
    if(C[i].l > x) continue;
    if(C[i].c == 1)
      tmp = max(tmp,C[i].p);
    else
      t.push_back(C[i]);
  }
  if(tmp > 0)
    t.push_back((Card){tmp,1,0});
  // for(auto i : t){
  //   printf("p:%d c:%d l:%d\n",i.p,i.c,i.l);
  // }
  int S = t.size(),T = S + 1;
  int sum = 0;
  for(unsigned i = 0;i<t.size();i++){
    sum += t[i].p;
    if(t[i].c % 2 == 1)
      addedge(S,i,t[i].p);
    else
      addedge(i,T,t[i].p);
    if(t[i].c % 2 == 0) continue; 
    for(unsigned j = 0;j<t.size();j++)if(i!=j){
      if(pri[t[i].c + t[j].c] == 0)
        addedge(i,j,inf);
    }
  }
  return sum - dinic(S,T) >= k;
}

void init(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=n;i++){
    int p,c,l;
    scanf("%d %d %d",&p,&c,&l);
    C[i] = (Card){p,c,l};
  }
  for(int i = 2;i<=200000;i++){
    if(pri[i] != 0) continue;
    for(int j = 2;i*j<=200000;j++){
      pri[i*j] = 1;
    }
  }
  // printf("fuck\n");
}


void solve(){
  int L = 1,R = 101;
  while(L != R){
    int mid = (L+R)/2;
    int t = check(mid);
    // printf("m:%d t:%d\n",mid,t);
    if(t)
      R = mid;
    else
      L = mid+1;
  }
  printf("%d\n",L==101?-1:L);
}

int main(){
  init();
  solve();
  return 0;
}