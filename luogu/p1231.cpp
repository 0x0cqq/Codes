//#include <bits/stdc++.h>
#include <cstdio>
#include <queue>
#include <algorithm>
#define MAXN 100000
using namespace std;

inline void qr(int &x){
  x = 0;char ch = getchar();
  while(ch<'0'||ch>'9'){
    ch = getchar();
  }
  while(ch>='0'&&ch<='9'){
    x = (x<<3)+(x<<1)+ch-48;
    ch = getchar();
  }
}

int dis[MAXN],cur[MAXN],fir[MAXN],n1,n2,n3,m1,m2,s,t,cnt = 2;

struct Edge{
  int from,to,flow,cap;
  int next;
}edge[MAXN<<3];

bool bfs(){
  queue<int> q;
  memset(dis,0,sizeof(dis));
  memcpy(cur,fir,sizeof(fir));
  q.push(s);dis[s] = 1;
  while(!q.empty()){
    int nown = q.front();q.pop();
    for(int e = fir[nown];e!=0;e = edge[e].next){
      int v = edge[e].to;
      if(dis[v] == 0&&edge[e].cap > edge[e].flow){
        dis[v] = dis[nown]+1;
        q.push(v);
        if(v == t)
            return dis[t];
      }
    }
  }
  return dis[t];
}

int dfs(int nown, int limit = 0x3f3f3f3f){
  if(nown == t||limit == 0){
    return limit;
  }
  for(int &e = cur[nown];e != 0;e = edge[e].next){
    int v = edge[e].to;
    if(dis[v] == dis[nown]+1 && edge[e].flow < edge[e].cap){
      int f = dfs(v,min(limit,edge[e].cap - edge[e].flow));
      if(f>0){
        edge[e].flow += f;
        edge[e^1].flow -= f;
        return f;
      }
    }
  }
  return 0;
}

int dinic(){
  int ans = 0,f;
  while(bfs()){
    while((f = dfs(s))>0){
      ans+=f;
    }
  }
  return ans;
}

void addedge(int a, int b, int c){
  edge[cnt].from = a,edge[cnt].to = b;
  edge[cnt].cap = c,edge[cnt].flow = 0;
  edge[cnt].next = fir[a];fir[a] = cnt;
  cnt++;
  edge[cnt].from = b,edge[cnt].to = a;
  edge[cnt].cap = 0,edge[cnt].flow = 0;
  edge[cnt].next = fir[b];fir[b] = cnt;
  cnt++;
}

int main(){
  qr(n1);qr(n2);qr(n3);
  s = n1+n1+n2+n3+2;t = n1+n1+n2+n3+3;
  scanf("%d",&m1);
  int a,b;
  for(int i = 1;i<=m1;i++){
    qr(a);qr(b);
    addedge(b,n2+a,1);
  }
  scanf("%d",&m2);
  for(int i = 1;i<=m2;i++){
    qr(a);qr(b);
    addedge(n1+n2+a,n1+n2+n1+b,1);
  }
  for(int i = 1;i<=n2;i++){
    addedge(s,i,1);
  }
  for(int i = 1;i<=n1;i++){
    addedge(n2+i,n2+n1+i,1);
  }
  for(int i = 1;i<=n3;i++){
    addedge(n1+n2+n1+i,t,1);
  }
  printf("%d\n",dinic());
  return 0;
}