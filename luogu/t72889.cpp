#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1100000;

int n,m,t,q;
int s[MAXN],cnt[MAXN],tmpcnt[MAXN];
vector<int> v[MAXN];
int r[MAXN];

vector<int> ans;

int main(){
  scanf("%d %d %d",&n,&t,&q);
  for(int i = 1;i<=t;i++){
    scanf("%d",&s[i]);
    cnt[s[i]]++;
  }
  for(int i = 1;i<=n;i++){
    int len;
    scanf("%d",&len);
    for(int j = 1;j<=len;j++){
      int t;
      scanf("%d",&t);
      v[i].push_back(t);
    }
  }
  scanf("%d",&m);
  for(int i = 1;i<=m;i++){
    scanf("%d",&r[i]);
  }
  int ANS = 0;
  for(int i = 1;i<=q;i++){
    int tmp = (i-1)%m + 1;
    for(auto x : v[tmp]) ans.push_back(x);
    memset(tmpcnt,0,sizeof(tmpcnt));
    int CNT = 0;
    if(ans.size() < t) continue;
    for(auto it = ans.rbegin();;it++){
      if(CNT == t) break;
      CNT++;
      tmpcnt[*it]++;
    }
    for(int i = 0;i<MAXN;i++){
      if(cnt[i] != tmpcnt[i]){
        break;
      }
      if(i == MAXN - 1) ANS++;
    }
  }
  printf("%d\n",ANS);
}