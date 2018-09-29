#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define ll long long
#define ull unsigned long long
using namespace std;

const int MAXN = 1000100,MAXL = 51000,N = 18,sigma_size = 26;

int n;
char s[N][MAXN];
int len[N][N];

struct AC{
  int c[MAXN][sigma_size],end[MAXN],f[MAXN],depth[MAXN];
  int ty[MAXN],endpos[N];
  int root,cnt;
  void insert(char *str,int num){
    int n = strlen(str),nown = 0;

    for(int i = 0;i<n;i++){
      int s = str[i] - 'a';
      if(!c[nown][s]) c[nown][s] = ++cnt;
      depth[nown] = i;
      ty[nown] |= (1<<num);

      nown = c[nown][s];
    }
    depth[nown] = n;
    ty[nown] |= (1<<num);
    end[nown] = num,endpos[num] = nown;
  }
  void getfail(){
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
        if(!c[nown][i]){
          c[nown][i] = c[f[nown]][i];
        }
        else{
          f[c[nown][i]] = c[f[nown]][i];
          q.push(c[nown][i]);
        }
      }
    }
    // for(int i = 0;i<=cnt;i++){
    //   printf("i:%d f:%d end:%d ty:%d\n",i,f[i],end[i],ty[i]);
    // }
  }
  void calc(int num){
    int nown = endpos[num];
    while(true){
      for(int i = 1;i<=N;i++){
        if((ty[nown]&(1<<i))!=0 && len[num][i]==0){
          len[num][i] = depth[nown];
        }
      }
      if(nown == 0) break;
      nown = f[nown];
    }
    len[num][num] = -1;
  }
}T;

const ull H = 31;

const ull MOD1 = 1000000007,MOD2 = 1000000009;

struct Hash{
  int n;
  ll _hash1[MAXL],_hash2[MAXL],pow1[MAXL],pow2[MAXL];
  void init(char *str){
    n = strlen(str);
    pow1[0] = pow2[0] = 1; 
    for(int i = 1;i<=n;i++){
      pow1[i] = (pow1[i-1] * H)%MOD1;
      pow2[i] = (pow2[i-1] * H)%MOD2;
    }
    for(int i = 1;i<=n;i++){
      _hash1[i] = (_hash1[i-1]*H+str[i-1])%MOD1;
      _hash2[i] = (_hash2[i-1]*H+str[i-1])%MOD2;
    }
  }
  ll h1(int l,int r){
    l++,r++;
    return (_hash1[r] - (_hash1[l-1]*pow1[r-l+1])%MOD1+MOD1)%MOD1;
  }
  ll h2(int l,int r){
    l++,r++;
    return (_hash2[r] - (_hash2[l-1]*pow2[r-l+1])%MOD2+MOD2)%MOD2;
  }
}S[N];


int vis[MAXN];

bool check(int i,int j){
  int l1 = S[i].n,l2 = S[j].n;
  if(l1 > l2){
    return false;
  }
  if(l1 == l2){
    if(S[i].h1(0,l1-1) == S[j].h1(0,l1-1))
      return i > j;
    else
      return false;
  }
  ll t = S[i].h1(0,l1-1);
  for(int w = 0;w+l1<=l2;w++){
    if(t == S[j].h1(w,w+l1-1))
      return true;
  }
  return false;
}

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%s",s[i]);
    T.insert(s[i],i);
    S[i].init(s[i]);
  }
  T.getfail();
  for(int i = 1;i<=n;i++)
    T.calc(i);
  // for(int i = 1;i<=n;i++){
  //   for(int j = 1;j<=n;j++){
  //     printf("i,j:%d %d num:%d\n",i,j,len[i][j]);
  //   }
  // }
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=n;j++)if(i!=j){
      if(check(i,j)){
        vis[i] = 1;
      }
    }
  }
  // for(int i = 1;i<=n;i++){
  //   printf("vis:%d\n",vis[i]);
  // }
}

static int newnum[N],lst[N];
static int tcnt = 0,l[N][N],lt[N];
int dp[MAXN][N],nex[MAXN][N];

int dfs(int nowp,int last){
  if(nowp == (1<<(tcnt+1))-2){
    return 0;
  }
  if(dp[nowp][last] != 0){
    return dp[nowp][last];
  }
  int ans = 0x3f3f3f3f;
  for(int i = 1;i<=tcnt;i++){
    if((nowp & (1<<i)) == 0){
      int tmp = dfs(nowp|(1<<i),i)-l[last][i] + lt[i];
      if(tmp < ans)
        nex[nowp][last] = i;
      ans = min(ans,tmp);
    }
  }
  return dp[nowp][last] = ans;
}


void solve(){
  for(int i = 1;i<=n;i++){
    if(vis[i]) continue;
    newnum[i] = ++tcnt;
    lst[tcnt] = i;
    lt[tcnt] = strlen(s[i]);
  }
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=n;j++){
      if(vis[i] || vis[j]) continue;
      l[newnum[i]][newnum[j]] = len[i][j];
    }
  }
  // for(int i = 1;i<=tcnt;i++){
  //   printf("%d:%d\n",i,lst[i]);
  //   for(int j = 1;j<=tcnt;j++){
  //     printf("%d %d:%d\n",i,j,l[i][j]);
  //   }
  // }
  printf("%d\n",dfs(0,0));
  static char ans[MAXN];
  int nowp = 0,last = 0;
  int tt = 0;
  do{
    int _nex = nex[nowp][last];
    //printf("nex:%d\n",_nex);
    for(int i = l[last][_nex];i<lt[_nex];i++){
      ans[tt++] = s[lst[_nex]][i];
    }
    nowp = nowp | (1<<_nex) ,last = _nex;
  }while(nowp != (1<<(tcnt+1))-2);
  printf("%s\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}