#include <cstdio>
using namespace std;

const int MAXN= 510000;

struct Edge{
  int to,nex;
  double q;
}edge[MAXN*2];int ecnt = 2;
int fir[MAXN];
void addedge(int a,int b,double q){
  edge[ecnt] = (Edge){b,fir[a],q};
  fir[a] = ecnt++;
}

int n;
double p[MAXN];
double f[MAXN],g[MAXN],w[MAXN];
double s(double i,double j){
  return i+j-i*j;
}

void dfs1(int x,int fa){
  f[x] = 1;
  for(int nowe = fir[x];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;double q = edge[nowe].q;
    if(v == fa) continue;
    dfs1(v,x);
    w[v] = s(f[v],1-q);
    f[x] *= w[v];
  }
  f[x] *= (1-p[x]);
}

void dfs2(int x,int fa){
  for(int nowe = fir[x];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;double q = edge[nowe].q;
    if(v == fa) continue;
    if(w[v] != 0){
      g[v] = s(1-q,g[x] * f[x] / w[v]);
    }
    dfs2(v,x);
  }
}

void solve(){
  g[1] = 1;
  dfs1(1,0),dfs2(1,0);
  double ans = 0;
  for(int i = 1;i<=n;i++){
    //printf("f:%lf g:%lf\n",f[i],g[i]);
    ans += 1-f[i]*g[i];
  }
  printf("%.6lf\n",ans);
}

void init(){
  scanf("%d",&n);
  for(int i = 2;i<=n;i++){
    int a,b,p;
    scanf("%d %d %d",&a,&b,&p);
    addedge(a,b,double(p)/100);
    addedge(b,a,double(p)/100);
  }   
  for(int i = 1;i<=n;i++){
    scanf("%lf",&p[i]);
    p[i]/=100;
  }
}

int main(){
  init();
  solve();
  return 0;
}