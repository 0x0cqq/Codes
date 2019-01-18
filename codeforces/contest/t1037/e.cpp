#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n,m,k;
int s[MAXN],t[MAXN];
int d[MAXN];
int ans[MAXN],vis[MAXN];
vector<int> edge[MAXN];

pair<int,int> mk(int x,int y){
  return x > y ? make_pair(y,x):make_pair(x,y);
}

set<pair<int,int> > S;

queue<int> q;

int main(){
  scanf("%d %d %d",&n,&m,&k);
  for(int i = 1;i<=m;i++){
    scanf("%d %d",&s[i],&t[i]);
    edge[s[i]].push_back(t[i]);
    edge[t[i]].push_back(s[i]);
    d[s[i]]++,d[t[i]]++;
  }
  int cnt = n;
  for(int i = 1;i<=n;i++){
    if(d[i] < k){
      // printf("%d\n",i);
      q.push(i);
      vis[i] = 1;
      cnt--;
    }
  }
  while(!q.empty()){
    int now = q.front();q.pop();
    for(unsigned i = 0;i<edge[now].size();i++){
      int v = edge[now][i];
      if(S.count(mk(now,v))) continue;
      S.insert(mk(now,v));
      d[now]--,d[v]--;
      if(d[v] < k && vis[v] == 0){
        q.push(v);
        vis[v] = 1;
        cnt--;
      }
    }
  }
  for(int i = m;i>=1;--i){
    // printf("%d:%d\n",i,cnt);
    ans[i] = cnt;
    if(vis[s[i]] || vis[t[i]] || S.count(mk(s[i],t[i])))
      continue;
    S.insert(mk(s[i],t[i]));
    d[s[i]]--,d[t[i]]--;
    if(d[s[i]] < k && vis[s[i]] == 0){
      q.push(s[i]);vis[s[i]] = 1;
      cnt--;
    }
    if(d[t[i]] < k && vis[t[i]] == 0){
      q.push(t[i]);vis[t[i]] = 1;
      cnt--;
    }

    while(!q.empty()){
      int now = q.front();q.pop();
      for(unsigned i = 0;i<edge[now].size();i++){
        int v = edge[now][i];
        if(S.count(mk(now,v))) continue;
        d[now]--,d[v]--;
        if(d[v] < k && vis[v] == 0){
          S.insert(mk(now,v));
          q.push(v);
          vis[v] = 1;
          cnt--;
        }
      }
    }
    
  }
  // for(int i = 1;i<=n;i++){
  //   printf("%d ",d[i]);
  // }
  // printf("\n");
  for(int i = 1;i<=m;i++){
    printf("%d\n",ans[i]);
  }
  return 0;
}