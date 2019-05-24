#include <bits/stdc++.h>
#define MAXN 210000
// #define pb push_back
// #define mp make_pair
#define fir first
#define sec second
#define file(s) freopen(s".in", "r", stdin),freopen(s".out", "w", stdout)
using namespace std;
typedef long long ll;
template <typename T> bool chkmax(T &x,T y) { return x < y ? x = y , 1 : 0;}
template <typename T> bool chkmin(T &x,T y) { return x > y ? x = y , 1 : 0;}
template <typename T> void read(T &x) {
	char ch = getchar(); int f = 1; x = 0;
	while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	x *= f;
}

struct Edge{
  int to;ll len;
};
vector<Edge> edge[MAXN];
void addedge(int a,int b,ll c){
  edge[a].push_back((Edge){b,c});
}
vector<int> point,up;

int n,t;
ll f[MAXN],s[MAXN],p[MAXN],q[MAXN],l[MAXN];
ll dep[MAXN],ans[MAXN];
int siz[MAXN],maxs[MAXN],vis[MAXN],SZ,RT;
int st[MAXN],top;
double cals(int i,int j){// dep[i] < dep[j]
  // printf("cals:%d %d\n",i,j);
  return 1.0 * (ans[i] - ans[j])/(dep[i] - dep[j]);
}
void insp(int x){// 往凸包里面插入一个点 x (这个凸包是倒着插入的)
  while(top >= 2 && cals(x,st[top]) >= cals(st[top],st[top-1])) top--;
  st[++top] = x;// printf("insp: top:%d x:%d\n",top,x);
}
bool cmp(int x,int y){ // 看哪个点走的更近
  return dep[x]-l[x] > dep[y]-l[y];
}
void dfs0(int x){// getdep
  for(auto e : edge[x])
    dep[e.to] = dep[x] + e.len,dfs0(e.to);
}
void dfs1(int x){// 加入point
  point.push_back(x);
  for(auto e : edge[x]) 
    if(!vis[e.to]) dfs1(e.to);
}
void getroot(int x){
  siz[x] = 1;maxs[x] = 0;
  for(auto e : edge[x])
    if(!vis[e.to]){
      getroot(e.to),siz[x] += siz[e.to];
      chkmax(maxs[x],siz[x]);
    }
  chkmax(maxs[x],SZ - siz[x]);
  if(maxs[x] < maxs[RT] && siz[x] > 1) RT = x;// 否则会死循环
}
int getp(int i){// 二分凸包，找到第一个斜率大于 p[i] 的
  int L = 1, R = top;
  if(top == 0) return 0;
  while(L <= R){
    int mid = (L+R)/2;
    double sL = mid == 1 ? 1e12 : cals(st[mid-1],st[mid]),
           sR = mid == top ? -1e12 : cals(st[mid],st[mid+1]);
    // printf("------mid:%d sL:%.2lf,sR:%.2lf\n",mid,sL,sR);
    if(sR <= p[i] && p[i] <= sL) return st[mid];
    if(sR > p[i]) L = mid+1;
    else R = mid-1;
  }
  assert(0);
  return 0;
}
void solve(int x,int sz){// 这里的 x 是联通块顶点
  // printf("x:%d sz:%d\n",x,sz);
  if(sz == 1) return;
  SZ = sz,RT = 0;getroot(x);
  int root = RT;
  // printf("  root:%d\n",root);
  for(auto e : edge[root]) vis[e.to] = 1;
  solve(x,sz-siz[root]+1);
  // 以下为 work 函数
  up.clear(),point.clear();top = 0;
  for(auto e : edge[root]) dfs1(e.to);
  sort(point.begin(),point.end(),cmp);
  for(int i = root;i != x;i = f[i]) up.push_back(i);
  up.push_back(x);
  // printf("point:\n");
  // for(auto i : point){
  //   printf("  i:%d dep:%lld\n",i,dep[i]);
  // }
  // printf("up:\n");
  // for(auto i : up){
  //   printf("  i:%d ans:%lld dep:%lld\n",i,ans[i],dep[i]);
  // }
  auto it = up.begin();
  for(auto i : point){
    while(it != up.end() && dep[*it] >= dep[i] - l[i]) 
      insp(*it),it++;
    // printf("getp:%d p:%lld\n",i,p[i]);
    int t = getp(i);
    if(t) chkmin(ans[i],ans[t] + (dep[i] - dep[t]) * p[i] + q[i]);
  }
  for(auto e : edge[root]) solve(e.to,siz[e.to]);
}

void init(){
  scanf("%d %d",&n,&t);maxs[0] = 1e9;
  for(int i = 2;i<=n;i++){
    scanf("%lld %lld %lld %lld %lld",&f[i],&s[i],&p[i],&q[i],&l[i]);
    addedge(f[i],i,s[i]);
  }
}

void solve(){
  dfs0(1);
  for(int i = 2;i<=n;i++) ans[i] = (1LL<<62);
  solve(1,n);
  for(int i = 2;i<=n;i++) printf("%lld\n",ans[i]);
}


int main(){
  init();
  solve();
  return 0;
}