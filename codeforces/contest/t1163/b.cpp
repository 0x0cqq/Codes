#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110000;

int n,N = 100000;
int a[MAXN];
int sum,maxn,cnt[MAXN],cnt2[MAXN];
set<int> S;


int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++) scanf("%d",&a[i]);
  int ans = 1;
  for(int i = 1;i<=n;i++){
    if(cnt[a[i]] == 0) sum++;
    int tmp = cnt[a[i]];
    cnt2[tmp]--,cnt2[tmp+1]++;
    cnt[a[i]]++;
    if(cnt2[tmp] == 0) S.erase(tmp);
    if(cnt2[tmp+1] == 1) S.insert(tmp+1);
    // printf("sum:%d size:%d begin:%d end:%d || %d %d\n",sum,int(S.size()),*S.begin(),*S.rbegin(),cnt2[*S.begin()],cnt2[*S.rbegin()]);
    if(sum == 1 || S.size() == 1 || (S.size() == 2 && ((*S.begin() == 1 && cnt2[1] == 1) || (cnt2[*S.rbegin()] == 1 && *S.rbegin() - *S.begin() == 1)))){
      ans = max(ans,i);
    }
  }
  printf("%d\n",ans);
}