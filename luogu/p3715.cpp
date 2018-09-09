#include <cstdio>
#include <cstring>
#include <queue>
#define ll long long
#define mod 1000000007
using namespace std;

const int MAXN = 1000,sigma_size = 30;


struct Matrix{
  static const int maxn = 210;
  ll num[maxn][maxn];
  Matrix(int op = 0){
    memset(num,0,sizeof(num));
    if(op==1) for(int i = 1;i<maxn;i++) num[i][i] = 1;
  }
  ll *operator[](const int n){
    return num[n];
  }
};

Matrix mul(Matrix &_a,Matrix &_b,const int siz){
  Matrix ans;
  for(int i = 1;i<=siz;i++){
    for(int j = 1;j<=siz;j++){
      for(int k = 1;k<=siz;k++){
        ans[i][j] = (ans[i][j] + _a[i][k] * _b[k][j])%mod; 
      }
    }
  }
  return ans;
}

Matrix pow(Matrix x,ll k,const int siz){
  Matrix ans(1);
  for(ll i = k;i;i>>=1,x = mul(x,x,siz)) if(i & 1) ans = mul(ans,x,siz);
  return ans;
}

namespace AC{
  int c[MAXN][sigma_size],end[MAXN],f[MAXN],root,cnt;
  void insert(char *s){
    int n = strlen(s),nown = root;
    for(int i = 0;i<n;i++){
      if(c[nown][s[i]-'a'] == 0)
        c[nown][s[i]-'a'] = ++cnt;
      nown = c[nown][s[i]-'a'];
    }
    end[nown] |= 1;
  }
  void get_fail(){
    queue<int> q;
    for(int i = 0;i<sigma_size;i++){
      if(c[root][i]){
        f[c[root][i]] = root;
        q.push(c[root][i]);
      }
    }
    while(!q.empty()){
      int nown = q.front();q.pop();
      for(int i = 0;i<sigma_size;i++){
        if(c[nown][i] == 0){
          c[nown][i] = c[f[nown]][i];
        }
        else{
          f[c[nown][i]] = c[f[nown]][i];
          end[c[nown][i]] |= end[f[c[nown][i]]];
          q.push(c[nown][i]);
        }
      }
    }
  }
  int trans(int start,char *s){
    if(end[start]) return -1;
    return s[0] == 0? start : trans(c[start][s[0]-'a'],s+1);
  }
}

int n,m,L;
int len[MAXN];
int tr[MAXN][MAXN];
char w[MAXN][MAXN];
char q[MAXN][MAXN];

void build(){
  // 将所有n个串在自动机上的每一个节点跑一遍
  AC::get_fail();
  for(int i = 0;i<=AC::cnt;i++){
    for(int j = 1;j<=n;j++){
      tr[i][j] = AC::trans(i,w[j]);
      //printf("tr[%d][%d]:%d\n",i,j,tr[i][j]);
    }
  }
}

ll solve1(){// l <= 100
  static ll dp[100000][MAXN];
  for(int i = 0;i<=AC::cnt;i++)
    if(AC::end[i] == 0) dp[0][i] = 1;
  for(int l = 1;l<=L;l++){
    for(int i = 0;i<=AC::cnt;i++){
      for(int j = 1;j<=n;j++){
        if(len[j] <= l && ~tr[i][j])
          dp[l][i] = (dp[l][i] + dp[l-len[j]][tr[i][j]])%mod;
      }
      //printf("l:%d i:%d dp:%lld\n",l,i,dp[l][i]);
    }
  }
  return dp[L][0];
}

ll solve2(){// l <= 1e8,len = 1 or 2
  ll ans = 0;
  Matrix t;int cnt = AC::cnt+1,siz = 2*cnt;
  static int vis1[MAXN],vis2[MAXN];
  for(int i = 0;i<cnt;i++){
    for(int w = 1;w<=n;w++){
      if(tr[i][w] == -1) continue;
      len[w] == 1?vis1[tr[i][w]]++:vis2[tr[i][w]]++;
    }
    // 右矩阵的上面cnt+1格，左矩阵的左上(cnt+1)*(cnt+1)格
    int ti = i+1;
    for(int j = 0;j<cnt;j++){
      int tj = j+1;
      t[ti][tj] = vis1[j];
      t[ti][tj+cnt] = vis2[j];
    }
    for(int w = 1;w<=n;w++){
      if(tr[i][w] == -1) continue;
      len[w] == 1?vis1[tr[i][w]]--:vis2[tr[i][w]]--;
    }
  }
  for(int i = 1;i<=cnt;i++){
    t[i+cnt][i] = 1;
  }
  t = pow(t,L,siz);
  for(int i = 1;i<=cnt;i++)
    ans = (ans + t[1][i])%mod;
  return ans%mod;
}

void init(){
  scanf("%d %d %d",&n,&m,&L);
  for(int i = 1;i<=n;i++){
    scanf("%s",w[i]);
    len[i] = strlen(w[i]);
  }
  for(int i = 1;i<=m;i++){
    scanf("%s",q[i]);
    AC::insert(q[i]);
  }
}

void solve(){
  //printf("%lld\n",L >= 100?solve1():solve2());
  printf("%lld\n",L <= 100?solve1():solve2());
}

int main(){
  init();
  build();
  solve();
  return 0;
}