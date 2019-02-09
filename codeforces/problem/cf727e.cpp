#include <bits/stdc++.h>
#define mp make_pair
#define fir first
#define sec second
#define ull unsigned long long
#define ll long long
using namespace std;

const int MAXN = 3100000;
const ull mod1 = 1000000007,mod2 = 1000000009,base = 131;

#define puu pair<ull,ull>

int n,k,g;
puu p[MAXN],h[MAXN],H1[MAXN],H2[MAXN];
char s[MAXN],*t[MAXN];
void init_hash(int len){
  p[0] = mp(1,1);
  for(int i = 1;i<=len;i++){
    p[i].fir = p[i-1].fir * base % mod1;
    p[i].sec = p[i-1].sec * base % mod2;
  }
  for(int i = 1;i<=len;i++){
    h[i].fir = (h[i-1].fir * base + s[i]-'a') % mod1; 
    h[i].sec = (h[i-1].sec * base + s[i]-'a') % mod2; 
  } 
}
puu _hash(int l,int r){//[l,r]
  puu ans;
  ans.fir = (h[r].fir + mod1 - h[l-1].fir * p[r-l+1].fir % mod1) % mod1;
  if(ans.fir< 0) ans.fir += mod1;
  ans.sec = (h[r].sec + mod2 - h[l-1].sec * p[r-l+1].sec % mod2) % mod2;
  if(ans.sec < 0) ans.sec += mod2;
  return ans;
}
puu _hash(char *S,int len){
  puu ans;
  for(int i = 1;i <= len;i++){
    ans.fir = (ans.fir * base + S[i] - 'a') % mod1;
    ans.sec = (ans.sec * base + S[i] - 'a') % mod2;
  }
  return ans;
}

void init(){
  scanf("%d %d",&n,&k);
  scanf("%s",s+1);
  for(int i = 1;i<=n*k;i++) s[n*k+i] = s[i];
  scanf("%d",&g);
  for(int i = 1;i<=g;i++){
    t[i] = new char[k+10];
    scanf("%s",t[i]+1);
  }
  init_hash(2*n*k);
  for(int i = 1;i <= n*k;i++) H1[i] = _hash(i,i+k-1);
  for(int i = 1;i <= g;i++) H2[i] = _hash(t[i],k);
  // for(int i = 1;i <= n*k;i++) cout << "(" << H1[i].first << " " << H1[i].second << ") ";
  // printf("\n");
  // for(int i = 1;i <= g;i++) cout << "(" << H2[i].first << " " << H2[i].second << ") ";
  // printf("\n");
}

map<puu,int> S;
int T1[MAXN],T2[MAXN];

vector<int> V[MAXN];
vector<int> ans;

void solve(){
  for(int i = 1;i<=n*k;i++) S[H1[i]] = 0;
  for(int i = 1;i<=g;i++)   S[H2[i]] = 0;
  int _ = 0;
  for(auto it = S.begin();it != S.end();it++) it->second = ++_;
  for(int i = 1;i<=n*k;i++) T1[i] = S[H1[i]];
  for(int i = 1;i<=g;i++)   T2[i] = S[H2[i]];
  // for(int i = 1;i <= n*k;i++) printf("%d ",T1[i]);
  // printf("\n");
  // for(int i = 1;i <= g;i++) printf("%d\n",T2[i]);
  for(int st = 1;st <= k;st++){
    for(int i = 1;i<=g;i++) V[T2[i]].push_back(i);
    bool flag = 0;
    for(int i = 1;i<=n;i++){
      int pos = (i-1) * k + st;
      if(!V[T1[pos]].empty()) {
        ans.push_back(V[T1[pos]].back());
        V[T1[pos]].pop_back();
      }
      else{
        // printf("b:%d\n",i);
        flag = 1;
        break;
      }
    }
    if(flag == 0){
      printf("YES\n");
      for(auto v : ans) printf("%d ",v);
      printf("\n");
      return ;
    }
    ans.resize(0);
    for(int i = 1;i<=g;i++) V[T2[i]].resize(0);
  }
  printf("NO\n");
}

int main(){
  init();
  solve();
  return 0;
}