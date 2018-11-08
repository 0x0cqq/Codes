#include <cstdio>
using namespace std;
const int MAXN = 1100;

struct Edge{
  int to,nex;
}edge[MAXN*2];int ecnt = 2;
int fir[MAXN];
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}

int n,B;

void init(){
  scanf("%d %d",&n,&B);
  for(int i = 2;i<=n;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    addedge(a,b);
    addedge(b,a);
  }
}

int stk[MAXN],top;
int col[MAXN],cap[MAXN],cnt;
// push stk[top++]
// pop stk[--top]

void dfs(int nown,int fa){
  //printf("nown:%d fa:%d\n",nown,fa);
  int s = top;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    dfs(v,nown);
    if(top - s >= B){
      int nowcol = ++cnt;
      cap[nowcol] = nown;
      while(top > s){
        int t = stk[--top];
        col[t] = nowcol;
      }
    }
  }
  stk[top++] = nown;
}

void solve(){
  dfs(1,0);
  while(top) col[stk[--top]] = cnt;
  printf("%d\n",cnt);
  for(int i = 1;i<=n;i++) printf("%d ",col[i]);
  printf("\n");
  for(int i = 1;i<=cnt;i++) printf("%d ",cap[i]);
  printf("\n");
}

int main(){
  init();
  solve();
  return 0;
}