#include <bits/stdc++.h>
using namespace std;const int N=5100;
int n,num[N],f[N],g[N],ans1,ans2;
int main(){
  scanf("%d",&n);
  for(int i=1;i<=n;i++) scanf("%d",&num[i]);
  num[0]=1e9,f[0]=0,g[0]=1;
  for(int i=1;i<=n;i++)for(int j=0;j<i;j++)if(f[j]+1>f[i]&&num[j]>num[i])f[i]=f[j]+1;
  for(int i=1;i<=n;i++){
    for(int j=0;j<i;j++){
      if(num[j]==num[i]&&f[j]==f[i])g[i]=0;
      if(f[j]+1==f[i]&&num[j]>num[i])g[i]+=g[j];
    }
  }
  for(int i=1;i<=n;i++){
    if(ans1<f[i])ans1=f[i],ans2=g[i];
    else if(ans1==f[i])ans2+=g[i];
  }
  printf("%d %d\n",ans1,ans2);
  return 0;
}