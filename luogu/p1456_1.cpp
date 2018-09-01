//It is coded by ning-mew on 8.28
#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+7;

int n,m;
int w[maxn],ls[maxn],rs[maxn],be[maxn],dis[maxn];

int getf(int x){return be[x]==x?x:be[x]=getf(be[x]);}
int merge(int x,int y){
  if(!x||!y)return x+y;
  if(w[x]<w[y])swap(x,y);
  rs[x]=merge(rs[x],y);
  if(dis[ls[x]]<dis[rs[x]])swap(rs[x],ls[x]);
  dis[x]=dis[rs[x]]+1;return x;
}
int pop(int x){
  int t = merge(ls[x],rs[x]);
  ls[x] = rs[x] = 0;
  return t;
}

void solve(){
  memset(ls,0,sizeof(ls)),memset(rs,0,sizeof(rs));
  memset(dis,0,sizeof(dis));
  for(int i=1;i<=n;i++){scanf("%d",&w[i]);be[i]=i;}
  scanf("%d",&m);
  for(int i=1;i<=m;i++){
    int x,y;scanf("%d%d",&x,&y);
    int fa1=getf(x),fa2=getf(y);
    if(fa1 == fa2){
      printf("-1\n");continue;
    }
    int A=pop(fa1),B=pop(fa2);w[fa1]/=2;w[fa2]/=2;
    if(A!=0)A=merge(A,fa1);else A=fa1;
    if(B!=0)B=merge(B,fa2);else B=fa2;A=merge(A,B);
    be[fa1]=be[fa2]=A;be[A]=A;
    printf("%d\n",w[A]);
  }
}

int main(){
  while(true){
    if(scanf("%d",&n) == 1){
      solve();
    }
    else{
      break;
    }
  }
  return 0;
}