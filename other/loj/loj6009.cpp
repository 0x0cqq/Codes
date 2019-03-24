#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXM = 110,MAXN = (1<<20)+10;

int n,m;
int T[MAXM],B1[MAXM],B2[MAXM],F1[MAXM],F2[MAXM];
char s[MAXM],t[MAXM];

int dis[MAXN],inq[MAXN];
int spfa(int s,int t){
  static queue<int> q;
  memset(dis,0x3f,sizeof(dis));
  dis[s] = 0,q.push(s);
  while(!q.empty()){
    int x = q.front();q.pop();inq[x] = 0;
    for(int i = 1;i<=m;i++){
      if(!((~x) & B1[i]) && !(x&B2[i])){
        int v = (x & (~F1[i])) | (F2[i]);
        if(dis[v] > dis[x] + T[i]){
          dis[v] = dis[x] + T[i];
          if(!inq[v]) q.push(v),inq[v] = 1;
        }
      }
    }
  }
  return dis[t];
}

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=m;i++){
    scanf("%d %s %s",&T[i],s,t);
    for(int j = 0;j<n;j++){
      if(s[j] == '+') B1[i] |= (1<<j);
      if(s[j] == '-') B2[i] |= (1<<j);
      if(t[j] == '-') F1[i] |= (1<<j);
      if(t[j] == '+') F2[i] |= (1<<j);
    }
  }
}

void solve(){
  int ans = spfa((1<<n)-1,0);
  printf("%d\n",ans==inf ? 0 : ans);
}

int main(){
  init(),solve();
  return 0;
}