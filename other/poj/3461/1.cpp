//It is coded by ning-mew on 8.11
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define base 131
#define int long long
using namespace std;

const int maxn=1e6+7;

int T,ans=0;
char ch[maxn],p[maxn];
int MOD[3]={19491001,19260817,20000909};
int Pow[3][maxn],Hash[3],pp[3][maxn];

void pre(){
  Pow[1][0]=Pow[2][0]=Pow[0][0]=1;
  for(int i=1;i<=500000;i++)
    Pow[k][i]=1ll*Pow[k][i-1]*base%MOD[k];
}
void work(){
  ans=0;
  scanf("%s",ch+1);scanf("%s",p+1);
  int n=strlen(ch+1),m=strlen(p+1);
  int k = 0;
  Hash[k]=0;
  for(int i=1;i<=n;i++){
    Hash[k]=(1ll*Hash[k]*base+ch[i]-'A')%MOD[k];
  }
  for(int i=1;i<=m;i++){
    pp[k][i]=(1ll*pp[k][i-1]*base+p[i]-'A')%MOD[k];
    if(i>=n){
      bool yep=1;
      if(((pp[k][i]-1ll*pp[k][i-n]*Pow[k][n]%MOD[k]+MOD[k])%MOD[k]!=Hash[k]){
        yep=0;
      }
      if(yep)ans++;
    }
  }printf("%lld\n",ans);
}
signed main(){
  scanf("%lld",&T);pre();
  for(int i=1;i<=T;i++)work();
  return 0;
}
