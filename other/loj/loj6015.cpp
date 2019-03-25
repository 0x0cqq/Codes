#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 10000,MAXM = MAXN*20;

namespace DINIC{
	int S,T;
	struct Edge{
		int from,to;
		int cap,flow;
		int nex;
	}edge[MAXM*2];
	int fir[MAXN],ecnt = 2;
	void addedge(int a,int b,int c){
    // printf("%d %d %d\n",a,b,c);
		edge[ecnt] = (Edge){a,b,c,0,fir[a]},fir[a] = ecnt++;
		edge[ecnt] = (Edge){b,a,0,0,fir[b]},fir[b] = ecnt++;
	}
	int dis[MAXN];
	bool bfs(){
		static queue<int> q; 
		memset(dis,0,sizeof(dis));
		dis[S] = 1,q.push(S);
		while(!q.empty()){
			int x = q.front();q.pop();
			for(int e = fir[x];e;e = edge[e].nex){
				int v = edge[e].to;
				if(!dis[v] && edge[e].cap > edge[e].flow){
					dis[v] = dis[x] + 1;
					q.push(v);
				}
			}
		}
		return dis[T];
	}
	int dfs(int x,int limit = inf){
		if(x == T || limit == 0) return limit;
		int sumf = 0;
		for(int e = fir[x];e;e = edge[e].nex){
			int v = edge[e].to;
			if(dis[v] == dis[x] + 1){
				int f = dfs(v,min(limit,edge[e].cap - edge[e].flow));
				sumf += f,limit -= f;
				edge[e].flow += f,edge[e^1].flow -= f;
				if(limit == 0) break;
			}
		}
		return sumf;
	}
	int dinic(int s,int t){
		S = s,T = t;static int ans = 0;
		while(bfs()) ans += dfs(s);
		return ans;
	}
}

int n,m,k;
int h[MAXN],p[MAXN],r[MAXN];vector<int> v[MAXN];

void init(){
	scanf("%d %d %d",&n,&m,&k);
	for(int i = 1;i<=m;i++){
		scanf("%d %d",&h[i],&r[i]);
		for(int j = 0;j < r[i];j++){
      int t;scanf("%d",&t);
      if(t == -1) t = n+1;
      v[i].push_back(t);
		}
	}
}

int _h(int x,int t){return (t)*(n+2) + x;}

void solve(){
  int S = 0,T = n+1;
  int ans = 0;
  while(true){
    if(ans > 500) break;
    ans++;
    for(int i = 0;i<=n;i++) DINIC::addedge(_h(i,ans-1),_h(i,ans),k);
    DINIC::addedge(_h(n+1,ans),_h(n+1,ans-1),k);
    for(int i = 1;i<=m;i++){
      int newp = p[i] == r[i]-1? 0 :p[i]+1; 
      DINIC::addedge(_h(v[i][p[i]],ans-1),_h(v[i][newp],ans),h[i]);
      p[i] = newp;
    }
    if(DINIC::dinic(S,T) >= k) break;
    // usleep(1000000);
  }
  printf("%d\n",ans > 500 ? 0 : ans);
}

int main(){
  init(),solve();
  return 0;
}