#include <bits/stdc++.h>
#define inf 1e18
#define pii pair<int,int>
using namespace std;

const int MAXN = 110000;
const int MAXQ = 500;

struct Query{
  int l,r,t,id;
  bool operator < (const Query &a)const{
    return t < a.t;
  }
}q[MAXN];

int n,m,Q;
int lb[MAXN],rb[MAXN],bl[MAXN];

struct P{
  int a,b,id;
  bool operator < (const P &x) const{
    if(b != x.b) return b < x.b;
    if(a != x.a) return a > x.a;
    return 0;
  }
}p[MAXN];


double calv(P x,int t){
  return double(x.a) + double(x.b)*t;
}

bool cmp(P x,P y,int t){// 前面优，返回1，后面优秀，返回 0
  if(calv(x,t) != calv(y,t))
    return calv(x,t) > calv(y,t);
  else
    return x.b > y.b;
}

double calj(P x,P y){
  if(x.b == y.b) return inf;
  return double(x.a-y.a)/(y.b-x.b);
}

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    scanf("%d %d",&p[i].a,&p[i].b);
    p[i].id = i;
  }
  for(int i = 1;i<=m;i++){
    scanf("%d %d %d",&q[i].l,&q[i].r,&q[i].t);
    q[i].id = i;
  }
  sort(q+1,q+m+1);
}

vector<P> V[MAXN];
vector<P> tmp;

void build(){
  Q = sqrt(n);
  for(int i = 1;i<=n;i++){
    bl[i] = (i-1)/Q + 1;
    if(bl[i] != bl[i-1]) lb[bl[i]] = i,rb[bl[i-1]] = i-1;
  }
  rb[bl[n]] = n;
  
  for(int x = 1;x<=bl[n];x++){
    int L = lb[x],R = rb[x];
    for(int i = L;i<=R;i++) V[x].push_back(p[i]);
    sort(V[x].begin(),V[x].end());
    // printf("x:%d lb:%d rb:%d\n",x,lb[x],rb[x]);
    // for(int i = 0;i< int(V[x].size());i++){
    //   printf("%d: a:%d b:%d id:%d\n",i,V[x][i].a,V[x][i].b,V[x][i].id);
    // }
    // printf("----------------------\n");
    tmp.clear();
    tmp.push_back(V[x][0]);
    for(int i = 1;i < int(V[x].size());i++){
      if(V[x][i].b != V[x][i-1].b) tmp.push_back(V[x][i]);
    }
    V[x].clear();
    V[x].push_back(tmp[0]);
    for(int i = 0;i < int(tmp.size());){
      int t = i;
      while((t <= int(tmp.size())-3 && 
        calj(tmp[i],tmp[t+1]) > calj(tmp[t+1],tmp[t+2]))){
        t++;
      }//t+1要不要
      // printf("i,t:%d %d\n",i,t);
      i = t+1;
      if(i < int(tmp.size())) V[x].push_back(tmp[i]);
    }
    // for(int i = 0;i< int(V[x].size());i++){
    //   printf("%d: a:%d b:%d id:%d\n",i,V[x][i].a,V[x][i].b,V[x][i].id);
    // }
  }
}

int now[MAXQ];
int ans[MAXN];


void solve(){
  for(int i = 1;i<=m;i++){
    int L = q[i].l,R = q[i].r,t = q[i].t;
    int BL = bl[L],BR = bl[R],tmp = 0;
    if(BL == BR){
      for(int i = L;i<=R;i++) if(cmp(p[i],p[tmp],t)) tmp = i;  
      ans[q[i].id] = tmp;
      continue;
    }
    for(int i = BL+1;i<=BR-1;i++){
      // printf("!\n");
      while(now[i]+1 < int(V[i].size()) && calv(V[i][now[i]],t) <= calv(V[i][now[i]+1],t))
        now[i]++;
      if(cmp(V[i][now[i]],p[tmp],t)) tmp = V[i][now[i]].id;
    }
    // printf("%d\n",tmp);
    for(int i = L;i<=rb[BL];i++) if(cmp(p[i],p[tmp],t)) tmp = i;  
    for(int i = lb[BR];i<=R;i++) if(cmp(p[i],p[tmp],t)) tmp = i;   
    ans[q[i].id] = tmp;
  }
  for(int i = 1;i<=m;i++){
    printf("%d\n",ans[i]);
  }
}

int main(){
  init();
  build();
  solve();
  return 0;
}