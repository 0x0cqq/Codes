#include <bits/stdc++.h>
#include <bits/extc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 210,MAXM = MAXN*50;
int n,m;
string name[MAXN];
int l[MAXN],r[MAXN];
map<string,int> M;
vector<int> ans[2];

namespace MCMF{
  int S,T,ansf,ansc;
  struct Edge{
    int from,to;
    int cap,flow;
    int cost,nex;
  }edge[MAXM*2];
  int fir[MAXN],ecnt = 2;
  void addedge(int a,int b,int c,int d){
    edge[ecnt] = (Edge){a,b,c,0, d,fir[a]},fir[a] = ecnt++;
    edge[ecnt] = (Edge){b,a,0,0,-d,fir[b]},fir[b] = ecnt++;
  }
  int dis[MAXN],inq[MAXN];
  bool spfa(){
    static queue<int> q;
    memset(dis,0x3f,sizeof(dis)),memset(inq,0,sizeof(inq));
    dis[S] = 0,q.push(S);
    while(!q.empty()){
      int x = q.front();q.pop(),inq[x] = 0;
      for(int e = fir[x];e;e = edge[e].nex){
        int v = edge[e].to;
        if(dis[v] > dis[x] + edge[e].cost && edge[e].cap > edge[e].flow){
          dis[v] = dis[x] + edge[e].cost;
          if(!inq[v]) q.push(v),inq[v] = 1;
        }
      }
    }
    return dis[T] < dis[0];
  }
  int dfs(int x,int limit = inf){
    if(x == T || limit == 0) return limit;
    int sumf = 0;inq[x] = 1;
    for(int e = fir[x];e;e = edge[e].nex){
      int v = edge[e].to;
      if(!inq[v] && dis[v] == dis[x] + edge[e].cost){
        int f = dfs(v,min(limit,edge[e].cap - edge[e].flow));
        sumf += f,limit -= f;
        edge[e].flow += f,edge[e^1].flow -= f;
        if(limit == 0) break;
      }
    }
    return sumf;
  }
  pair<int,int> solve(int s,int t){
    S = s,T = t,ansf = ansc = 0;
    while(spfa()){
      int f = dfs(s);
      ansf += f,ansc += f * dis[T];
    }
    return make_pair(ansf,ansc);
  }
  int vis[MAXN];
  void output(int x,int op){
    vis[x] = 1;
    if(1 <= x && x <= n) ans[op].push_back(x);
    for(int e = fir[x];e;e = edge[e].nex){
      int v = edge[e].to;
      if(edge[e].flow == 1 && vis[v] == 0){
        output(v,op);
        return;
      }
    }
  }
}


void init(){
  cin >> n >> m;
  for(int i = 1;i<=n;i++){cin >> name[i];M[name[i]] = i;}
  for(int i = 1;i<=m;i++){
    string s,t;
    cin >> s >> t;
    l[i] = M[s],r[i] = M[t];
  }
}

int in(int i){return i;}
int out(int i){return i+n;}

void solve(){
  int S = 2*n+1,T = S+1,flag = 0;
  MCMF::addedge(S,out(1),2,0),MCMF::addedge(in(n),T,2,0);
  for(int i = 1;i<=n;i++) MCMF::addedge(in(i),out(i),1,-1);
  for(int i = 1;i<=m;i++){
    if(l[i] > r[i]) swap(l[i],r[i]);
    if(l[i] == 1 && r[i] == n) flag = 1;
    MCMF::addedge(out(l[i]),in(r[i]),1,0);
  }
  pair<int,int> ANS = MCMF::solve(S,T);
  // printf("%d %d\n",ANS.first,ANS.second);
  if(ANS.first != 2 && flag == 0){
    cout << "No Solution!" << endl;
    return;
  }
  else{
    cout << -ANS.second + 2 << endl;
    MCMF::output(out(1),0);
    MCMF::output(out(1),1);
    cout << name[1] << endl;
    for(int i = 0;i < int(ans[0].size());i++) 
      cout << name[ans[0][i]] << endl;  
    for(int i = int(ans[1].size()) - 1;i >= 0;i--)
      cout << name[ans[1][i]] << endl;  
    cout << name[1] << endl;
  }
}

int main(){
  // freopen("in.txt","r",stdin);
  init(),solve();
  return 0;
}