#include <bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 2000,MAXM = MAXN*10;

namespace MCMF{
	int S,T,ansf,ansc;
	struct Edge{
		int from,to;
		int cap,flow;
		int cost,nex;
	}edge[MAXM*2];
	int fir[MAXN],ecnt = 2;
	void addedge(int a,int b,int c,int d){
		// printf("%lld %lld %lld %lld\n",a,b,c,d);
		edge[ecnt] = (Edge){a,b,c,0,d,fir[a]},fir[a] = ecnt++;
		edge[ecnt] = (Edge){b,a,0,0,-d,fir[b]},fir[b] = ecnt++;
	}
	int dis[MAXN],inq[MAXN];
	bool spfa(){
		static queue<int> q;
		memset(dis,0x3f,sizeof(dis));//distance
		dis[S] = 0,q.push(S);
		while(!q.empty()){
			int x = q.front();q.pop();inq[x] = 0;
			for(int e = fir[x];e;e = edge[e].nex){
				int v = edge[e].to;
				if(edge[e].cap > edge[e].flow && dis[v] > dis[x] + edge[e].cost){
					dis[v] = dis[x] + edge[e].cost;
					if(!inq[v]) q.push(v),inq[v] = 1;
				}
			}
		}
		return dis[T] < dis[0];
	}
	int dfs(int x,int limit = inf){
		if(x == T || limit == 0) return limit;
		int sumf = 0;inq[x] = 1;//in queue
		for(int e = fir[x];e;e = edge[e].nex){
			int v = edge[e].to;
			if(dis[v] == dis[x] + edge[e].cost && !inq[v]){
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
			memset(inq,0,sizeof(inq));
			ansf += f,ansc += f * dis[T];
		}
		return make_pair(ansf,ansc);
	}
}

namespace MAIN{

map<int,int> t;

int n,k;
int x0[MAXN],y0[MAXN],x1[MAXN],y1[MAXN];

int getv(int i){
  return (x0[i] - x1[i])*(x0[i] - x1[i]) + (y0[i] - y1[i])*(y0[i] - y1[i]);
}

void init(){
	scanf("%lld %lld",&n,&k);
	for(int i = 1;i<=n;i++){
		scanf("%lld %lld",&x0[i],&y0[i]);
		scanf("%lld %lld",&x1[i],&y1[i]);
		if(x0[i] > x1[i]) swap(x0[i],x1[i]),swap(y0[i],y1[i]);
		t[x0[i]] = 0,t[x1[i]] = 0;
	}
	int tcnt = 0;
	for(map<int,int>::iterator it = t.begin();it != t.end();it++){
		it->second = ++tcnt;
	}
}
int in(int i){return i;}
int out(int i){return i + t.size();}


void solve(){
	int S = t.size()*2 + 1,T = S+1;
	MCMF::addedge(S,in(1),k,0),MCMF::addedge(out(t.size()),T,k,0);
	for(int i = 1;i<=(int)(t.size());i++){
    MCMF::addedge(in(i),out(i),k,0);
  }
	for(int i = 1;i<(int)(t.size());i++){
    MCMF::addedge(out(i),in(i+1),k,0);
  }
  for(int i = 1;i<=n;i++){
    if(x0[i] == x1[i])
      MCMF::addedge(in(t[x0[i]]),out(t[x1[i]]),1,-(int)(sqrt(getv(i))));
    else
      MCMF::addedge(out(t[x0[i]]),in(t[x1[i]]),1,-(int)(sqrt(getv(i))));
  }
	printf("%lld\n",-(MCMF::solve(S,T).second));
}

}

signed main(){
	MAIN::init(),MAIN::solve();
	return 0;
}