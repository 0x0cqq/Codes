#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int T;
int n;

int ans[MAXN];
struct Line{
  int l,r,id;
}p[MAXN];

bool cmp(Line a,Line b){
  if(a.l != b.l)
    return a.l < b.l;
  else
    return a.r < b.r;
}

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d %d",&p[i].l,&p[i].r);
    p[i].id = i;
  }
  sort(p+1,p+n+1,cmp);
}



void solve(){
  int nowmax = 0;
  for(int i = 1;i<=n;i++){
    nowmax = max(nowmax,p[i].r);
    if(i != n && nowmax  < p[i+1].l){
      for(int j = 1;j<=i;j++){
        ans[p[j].id] = 1;
      }
      for(int j = i+1;j<=n;j++){
        ans[p[j].id] = 2;
      }
      for(int i = 1;i<=n;i++){
        printf("%d ",ans[i]);
      }
      printf("\n");
      return;
    }
  }
  printf("%d\n",-1);
}

int main(){
  scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    init();
    solve();
  }
  return 0;
}