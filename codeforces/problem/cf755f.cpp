#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010000;

int n,k;
int p[MAXN],cn[MAXN];

int getmin(){
  int sum = 0;
  static int f[MAXN];
  memset(f,0x3f,sizeof(f));
  f[0] = 0;
  for(int i = 1;i<=n;i++){
    if(cn[i] == 0) continue;
    sum += i * cn[i];
    for(int k = 0;k+i<=sum;k++){
      if(f[k] >= cn[i]) continue;
      if(f[k+i] > f[k] + 1){
        f[k+i] = f[k] + 1;
      }
    }
    for(int k = 0;k<=sum;k++){
      f[k] = f[k] <= cn[i] ? 0 : 0x3f3f3f3f;
    }
  }
  return f[k] == 0?k:k+1;
}

int getmax(){
  int tmp = 0;
  for(int i = 1;i<=n;i++) tmp += i/2 * cn[i];
  return tmp >= k?2*k:min(n,2*tmp + (k-tmp));
}


int main(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=n;i++) scanf("%d",&p[i]);
  static int vis[MAXN];
  for(int i = 1;i<=n;i++){
    if(vis[i] == 1) continue;
    int nown = p[i],cnt = 1;
    while(nown != i){
      vis[nown] = 1;
      nown = p[nown];
      cnt++;
    }
    vis[i] = 1;
    cn[cnt]++;
  }
  printf("%d %d\n",getmin(),getmax());
  return 0;
}