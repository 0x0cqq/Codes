#include<bits/stdc++.h>
#define int long long
#define LL long long
#define Pair pair<int,int>
#define MP(x,y) make_pair(x,y)
using namespace std;

const int N=100007,M=200007;
const LL inf=(1ll<<60),MOD=1e9+7;

int n,m,S,T;
int head[N],cnt=0;
int Head[N],Cnt=0;
int HHead[N],CCnt=0;
struct EEdge{int nxt,to,dis;}edge[M*2],Edge[M*2],EEdge[M*2];
LL dist[N],Dist[N],way1[N],way2[N],Ans=0;
int inin[N],ininin[N];
bool vis[N],pu[N];

void add(int from,int to,int dis){
  edge[++cnt].nxt=head[from];edge[cnt].to=to;
  edge[cnt].dis=dis;head[from]=cnt;
}
void Add(int from,int to,int dis){
  Edge[++Cnt].nxt=Head[from];Edge[Cnt].to=to;
  Edge[Cnt].dis=dis;Head[from]=Cnt;
  //cout<<"Edge: "<<from<<' '<<to<<' '<<dis<<endl;
  swap(from,to);
  EEdge[++CCnt].nxt=HHead[from];EEdge[CCnt].to=to;
  EEdge[CCnt].dis=dis;HHead[from]=CCnt;
  //cout<<"EEdge:"<<from<<' '<<to<<' '<<dis<<endl;
}
void dij(){
  priority_queue<Pair>Q;while(!Q.empty())Q.pop();
  for(int i=1;i<=n;i++)dist[i]=Dist[i]=inf;
  memset(vis,0,sizeof(vis));
  dist[S]=0;Q.push(MP(0,S));
  while(!Q.empty()){
    int u=Q.top().second;Q.pop();
    if(vis[u])continue;vis[u]=1;
    for(int i=head[u];i!=0;i=edge[i].nxt){
      int v=edge[i].to;
      if(dist[v]>dist[u]+edge[i].dis){
	dist[v]=dist[u]+edge[i].dis;
	Q.push(MP(-dist[v],v));
      }
    }
  }
  memset(vis,0,sizeof(vis));
  Dist[T]=0;Q.push(MP(0,T));
  while(!Q.empty()){
    int u=Q.top().second;Q.pop();
    if(vis[u])continue;vis[u]=1;
    for(int i=head[u];i!=0;i=edge[i].nxt){
      int v=edge[i].to;
      if(Dist[v]>Dist[u]+edge[i].dis){
	Dist[v]=Dist[u]+edge[i].dis;
	Q.push(MP(-Dist[v],v));
      }
    }
  }
}
void rebuild(){
  memset(pu,0,sizeof(pu));
  for(int u=1;u<=n;u++){
    for(int i=head[u];i!=0;i=edge[i].nxt){
      int v=edge[i].to;
      if(dist[u]+edge[i].dis+Dist[v]==dist[T]){
	  Add(u,v,edge[i].dis);
	  ++inin[v];++ininin[u];
	  pu[u]=pu[v]=1;
      }
    }
  }
}
void topsort(){
  queue<int>Q;while(!Q.empty())Q.pop();
  Q.push(S);way1[S]=1;
  while(!Q.empty()){
    int u=Q.front();Q.pop();
    for(int i=Head[u];i!=0;i=Edge[i].nxt){
      int v=Edge[i].to;--inin[v];
      way1[v]+=way1[u];if(!inin[v])Q.push(v);
    }
  }
  Q.push(T);way2[T]=1;
  while(!Q.empty()){
    int u=Q.front();Q.pop();
    for(int i=HHead[u];i!=0;i=EEdge[i].nxt){
      int v=EEdge[i].to;--ininin[v];
      way2[v]+=way2[u];if(!ininin[v])Q.push(v);
    }
  }
}
void work(){
  Ans=way1[T]*way2[S]%MOD;//cout<<"Ans:"<<Ans<<endl;
  for(int u=1;u<=n;u++){
    if(!pu[u])continue;
    if(2*dist[u]==dist[T]){
      //cout<<"pl:"<<u<<endl;
      Ans=((Ans-way1[u]*way2[u]%MOD)%MOD+MOD)%MOD;
      continue;
    }
    int sum = 0;
    for(int i=Head[u];i!=0;i=Edge[i].nxt){
        sum1 += way1[u];
    }
    for(int i=Head[u];i!=0;i=Edge[i].nxt){
      int v=Edge[i].to;
      //cout<<u<<' '<<v<<endl;
      if(2*dist[u]<dist[T]&&2*dist[v]>dist[T]){
	Ans=((Ans-way1[u]*way2[v]%MOD)%MOD+MOD)%MOD;
// 	cout<<"pl:"<<u<<' '<<v<<' '<<Ans<<endl;
      }
    }
  }printf("%lld\n",Ans%MOD);return;
}
signed main(){
  scanf("%lld%lld",&n,&m);
  scanf("%lld%lld",&S,&T);
  for(int i=1;i<=m;i++){
    int x,y,z;scanf("%lld%lld%lld",&x,&y,&z);
    add(x,y,z);add(y,x,z);
    /*for(int j=head[x];j!=0;j=edge[j].nxt){
      int v=edge[j].to;if(v==y){printf("YES");exit(0);}
      }*/
  }
  dij();
  //cout<<"-------------dist Dist--------------"<<endl;
  //for(int i=1;i<=n;i++)cout<<i<<' '<<dist[i]<<' '<<Dist[i]<<endl;
  //cout<<"------------------------------------"<<endl;

  rebuild();
//   cout<<"-------------inin ininin--------------"<<endl;
//   for(int i=1;i<=n;i++)cout<<i<<' '<<inin[i]<<' '<<ininin[i]<<endl;
//   cout<<"--------------------------------------"<<endl;

  topsort();
  //cout<<"-------------way1 way2--------------"<<endl;
  //for(int i=1;i<=n;i++)cout<<i<<' '<<way1[i]<<' '<<way2[i]<<endl;
  //cout<<"------------------------------------"<<endl;

//   cout<<"-------------work-------------"<<endl;
  work();
  return 0;
}
