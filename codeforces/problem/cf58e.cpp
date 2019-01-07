#include <bits/stdc++.h>
#define ll long long
using namespace std;

#define fuck printf("fuck\n")

const int inf = 1e9;

ll a[20],w[20];
ll p[20];
int dp[13][13][13][13][2];
struct Node{
  int x,y,z,a,b,c,q;
}last[13][13][13][13][2];
int get1(int k){return a[0]/p[k] == 0?0:(a[0]/p[k])%10;}
int get2(int k){return a[1]/p[k] == 0?0:(a[1]/p[k])%10;}
int get3(int k){return a[2]/p[k] == 0?0:(a[2]/p[k])%10;}
int count(int x){int ans = 0;while(x){ans+=(x&1);x>>=1;}return ans;}
bool ch(int S,int i){return S & (1<<i);}

int dfs(int n,int i,int j,int k,int q){//最小需要添加的位数
  if(n > 11 || i > 11 || j > 11 || k > 11) return inf;
  // fuck;
  if(i >= w[0] && j >= w[1] && k >= w[2] && q == 0){
    // printf("n:%d i,j,k:%d %d %d q:%d ans:%d\n",n,i,j,k,q,0);
    return 0;
  }
  // fuck;
  if(dp[n][i][j][k][q] != -1) return dp[n][i][j][k][q];
  // printf("n:%d i,j,k:%d %d %d q:%d\n",n,i,j,k,q);
  int ans = inf;
  for(int x = 0;x<=9;x++){
    for(int y = 0;y<=9;y++){
      int now = (x + y + q)%10,jin = (x + y + q)/10;
      int A = get1(i),B = get2(j),C = get3(k),tar = 0;
      if(A==x){tar|=1;}if(B==y){tar|=2;}if(C==now){tar|=4;}
      for(int S = 8-1;S>=0;S--){
        if((tar & S) == S){// S 是 tar 的子集
          int newans = 3 - ch(S,0) - ch(S,1) - ch(S,2) + dfs(n+1,i+ch(S,0),j+ch(S,1),k+ch(S,2),jin);
          if(newans < ans){
            ans = newans;
            last[n][i][j][k][q] = (Node){x,y,now,i+ch(S,0),j+ch(S,1),k+ch(S,2),jin};
          }
        }
      }
    }
  }
  // Node X = last[n][i][j][k][q];
  // printf("n:%d i,j,k:%d %d %d q:%d ans:%d last:%d %d %d %d\n",n,i,j,k,q,ans,X.a,X.b,X.c,X.q);
  return dp[n][i][j][k][q] = ans;
}

int main(){
  scanf("%lld+%lld=%lld",&a[0],&a[1],&a[2]);
  for(int i = 0;i<3;i++){w[i] = int(log10(a[i])+1);}
  // printf("%d %d %d:%d %d %d\n",a[0],a[1],a[2],w[0],w[1],w[2]);
  p[0] = 1;
  for(int i = 1;i<=12;i++)p[i] = p[i-1]*10;
  memset(dp,-1,sizeof(dp));
  int t = dfs(0,0,0,0,0);
  printf("%d\n",t);
  ll ansa = 0,ansb = 0,ansc = 0;
  int nowa = 0,nowb = 0,nowc = 0,nowq = 0;
  for(int i = 0;;i++){
    Node tmp = last[i][nowa][nowb][nowc][nowq];
    ansa += p[i] * tmp.x,ansb += p[i] * tmp.y,ansc += p[i] * tmp.z;
    nowa = tmp.a,nowb = tmp.b,nowc = tmp.c,nowq = tmp.q;
    if(nowa == 0 && nowb == 0 && nowc == 0 && nowq == 0){
      break;
    }
  }
  printf("%lld+%lld=%lld\n",ansa,ansb,ansc);
  return 0;
}