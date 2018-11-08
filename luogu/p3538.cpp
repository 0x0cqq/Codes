#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 510000;

#define ll long long
static const ll base = 29,mod = 1000000007;
ll h[MAXN],p[MAXN];
void init(char *s){
  int n = strlen(s);
  p[0] = 1;
  for(int i = 1;i<=n;i++) p[i] = p[i-1] * base % mod;
  for(int i = 1;i<=n;i++) h[i] = (h[i-1] * base + s[i-1]) % mod;
}
inline ll get_hash(int l,int r){
  ll t = (h[r] - p[r-l+1]*h[l-1])%mod;
  return t < 0?t+mod:t;
}
#undef ll

int n,m;
char s[MAXN];

bool vis[MAXN];
int prime[MAXN],cnt;
int f[MAXN];
inline void get_prime(int n){
  f[1] = 1;
  for(int i = 2;i<=n;i++){
    if(vis[i] == 0){
      prime[++cnt] = i;
      f[i] = i;
      //printf("prime!\n");
    }
    for(int j = 1;j <= cnt && i*prime[j] <= n;j++){
      vis[i*prime[j]] = 1;
      f[i*prime[j]] = prime[j];
      if(i % prime[j] == 0) break;
    }
    // printf("%d:%d\n",i,f[i]);
  }
}

void init(){
  scanf("%d",&n);
  get_prime(n);
  scanf("%s",s);
  init(s);
}

inline bool judge(int l,int r,int d){
  if((r-l+1) % d)
    return 0;
  else
    return get_hash(l,r-d) == get_hash(l+d,r);
}


inline int query(int l,int r){
  static int pp[MAXN];int cnt = 0;
  int len = (r-l+1);
  for(int x = len;x > 1;x /= f[x])
    pp[++cnt] = f[x];
  for(int i = 1;i<=cnt;i++){
    if(judge(l,r,len/pp[i]))
      len = len/pp[i];
  }
  return len;
}

void solve(){
  int l,r;
  scanf("%d",&m);
  for(int i = 1;i<=m;i++){
    scanf("%d %d",&l,&r);
    printf("%d\n",query(l,r));
  }   
}

int main(){
  init();
  solve();
  return 0;
}