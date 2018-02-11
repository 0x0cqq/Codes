#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 11;

int n,m,cnt,ans = 0,in[MAXN],dd[MAXN];
vector<int> edge[MAXN];


int dfs(int nown){
  if(edge[nown].size() == 0){
    return 1;
  }
  else{
    int res = 0;
    if(dd[nown]) return dd[nown];
    for(auto w = edge[nown].begin();w!=edge[nown].end();w++){
      int nextn = *w;
      res += dfs(nextn);
    }
    return dd[nown] = res; 
  }
}

int main(){
  scanf("%d %d",&n,&m);
  int a,b;
  for(int i = 1;i<=m;i++){
    scanf("%d %d",&a,&b);
    edge[a].push_back(b);
    in[b]++;
  }
  bool f = 1;
  for(int i = 1;i<=n;i++){
    if(in[i] == 0 && edge[i].size() != 0){
      f = 1;
      ans+=dfs(i);
    }
  }
  printf("%d\n",ans);
  return 0;
}