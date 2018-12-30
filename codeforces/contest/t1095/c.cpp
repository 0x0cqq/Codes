#include <bits/stdc++.h>
using namespace std;

int logn = 31;
priority_queue<int> Q;
vector<int> v;

int main(){
  int n,k;
  scanf("%d %d",&n,&k);
  for(int i = 0;i<logn;i++){
    if(n & (1<<i)){
      Q.push((1<<i));
    }
  }
  if(k > n || k < int(Q.size())){
    printf("NO\n");
    return 0;
  }
  int tmp = Q.size();
  for(int i = 1;i<=k-tmp;i++){
    int t = Q.top();
    Q.pop();
    Q.push(t/2),Q.push(t/2);
  }
  printf("YES\n");
  while(!Q.empty()){
    printf("%d ",Q.top());
    Q.pop();
  }
  printf("\n");
  return 0;
}